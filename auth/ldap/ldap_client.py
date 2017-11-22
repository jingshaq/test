#!/usr/bin/python
# -*- encoding=utf8 -*-

import ldap
from   ldap   import modlist

#----------------------------------------------------------
# LdapClient
#----------------------------------------------------------
class LdapClient(object):

    #----------------------------------------------------------
    # INIT
    #----------------------------------------------------------
    def __init__(self, ldap_host, ldap_base_dn, ldap_manager_password):

        self.ldap_base_dn       = ldap_base_dn
        self.ldap_manager_dn    = 'cn=Manager,%s' % ldap_base_dn
        self.ldap               = ldap.initialize(ldap_host)
        self.ldap.simple_bind_s(self.ldap_manager_dn, ldap_manager_password)

    #----------------------------------------------------------
    # SEARCH
    #----------------------------------------------------------
    def search_group(self, ldap_search_name):

        ldap_search_dn = 'ou=Group,%s'  % self.ldap_base_dn
        ldap_search_cn = 'cn=%s'        % ldap_search_name

        return self._search(ldap_search_dn, ldap_search_cn)

    def search_people(self, ldap_search_name):

        ldap_search_dn = 'ou=People,%s' % self.ldap_base_dn
        ldap_search_cn = 'uid=%s'       % ldap_search_name

        return self._search(ldap_search_dn, ldap_search_cn)

    def _search(self, ldap_search_dn, ldap_search_cn):

        row_ldif_list = self.ldap.search_s(ldap_search_dn,
                                           ldap.SCOPE_SUBTREE,
                                           ldap_search_cn,
                                           None)

        now_ldif_dict = {}

        for dn, entry in row_ldif_list:
            for _key, _value in entry.items():
                if _key != 'objectClass' :
                    now_ldif_dict[_key] =  _value[0]

            yield (dn, now_ldif_dict)

    #----------------------------------------------------------
    # ADD
    #----------------------------------------------------------
    def add_group(self, **keywords):

        keywords['objectclass'] = ['posixGroup', 'top']
        ldap_gropu_dn           = 'cn=%s,ou=Group,%s' % (keywords['cn'], self.ldap_base_dn)
        ldap_group_ldif         = modlist.addModlist(keywords)

        return self._add(ldap_gropu_dn, ldap_group_ldif)

    def add_people(self, **keywords):

        keywords['objectclass'] = ['account', 'posixAccount', 'top', 'shadowAccount']
        ldap_people_dn          = 'uid=%s,ou=People,%s' % (keywords['cn'], self.ldap_base_dn)
        ldap_people_ldif        = modlist.addModlist(keywords)

        return self._add(ldap_people_dn, ldap_people_ldif)

    def _add(self, dn, ldif):

        try :
            self.ldap.add_s(dn, ldif)
            return (0, dn)

        except ldap.ALREADY_EXISTS:
            return (1, 'already exists %s' % dn)

    #----------------------------------------------------------
    # DELETE
    #----------------------------------------------------------
    def delete_people(self, delete_name):

        ldap_delete_dn  = 'uid=%s,ou=People,%s' % (delete_name, self.ldap_base_dn)

        return self._delete(ldap_delete_dn)

    def delete_group(self, delete_name):

        ldap_delete_dn = 'cn=%s,ou=Group,%s'    % (delete_name, self.ldap_base_dn)

        return self._delete(ldap_delete_dn)

    def _delete(self, delete_dn):
        try :
            self.ldap.delete_s(delete_dn)
            return (0, delete_dn)

        except ldap.NO_SUCH_OBJECT, e:
            return (1, 'no such object %s' % delete_dn)

    #----------------------------------------------------------
    # MODIFY
    #----------------------------------------------------------
    def modify_people(self, name, change_ldif_dict):

        dn, now_ldif_dict = self.search_people(name).next()

        return self._modify(dn, now_ldif_dict, change_ldif_dict)


    def modify_group(self, name, change_ldif_dict):

        dn, now_ldif_dict = self.search_group(name).next()

        return self._modify(dn, now_ldif_dict, change_ldif_dict)


    def _modify(self, dn, now_ldif_dict, change_ldif_dict):

        new_ldif_dict = {}
        old_ldif_dict = {}

        for _key, _value in change_ldif_dict.items():
            if now_ldif_dict.has_key(_key):
                old_ldif_dict[_key] = now_ldif_dict[_key]
                new_ldif_dict[_key] = _value

        try :
            ldif = modlist.modifyModlist(old_ldif_dict, new_ldif_dict)
            self.ldap.modify_s(dn, ldif)
            return (0, dn, '%s > %s'  % (str(old_ldif_dict), str(new_ldif_dict)))

        except Exception, e:
            return (1, dn, e)

#----------------------------------------------------------
# SSHA python seeded salted sha password
# http://www.openldap.org/faq/data/cache/347.html
# > challenge_password = makeSecret('testing123')
# > checkPassword(challenge_password, 'testing123')
#----------------------------------------------------------
import os
import hashlib
from base64 import encodestring as encode
from base64 import decodestring as decode

def makeSecret(password):
    salt = os.urandom(4)
    h = hashlib.sha1(password)
    h.update(salt)
    return "{SSHA}" + encode(h.digest() + salt)

def checkPassword(challenge_password, password):
    challenge_bytes = decode(challenge_password[6:])
    digest = challenge_bytes[:20]
    salt = challenge_bytes[20:]
    hr = hashlib.sha1(password)
    hr.update(salt)
    return digest == hr.digest()

#----------------------------------------------------------
# TEST
#----------------------------------------------------------
def test():


    _LDAP_HOST      = 'ldap://172.16.1.215'
    _MANAGER_PASS   = 'zhu88jie'
    _BASE_DN        = 'dc=centos7,dc=com'

    a = LdapClient(_LDAP_HOST, _BASE_DN, _MANAGER_PASS)

    test_people(a)
    test_group(a)

def test_people(a):

    name      = 'user01'
    user_dict = { 'uid'           : name              ,
                  'cn'            : name              ,
                  'userPassword'  : makeSecret('pass'),
                  'uidNumber'     : '500'             ,
                  'gidNumber'     : '500'             ,
                  'homeDirectory' : '/home/hoge'      ,
                  'loginShell'    : '/bin/sh'         ,
                  'description'   : 'Description'     }

    print '\n#=== PEOPLE' + '=' * 80
    print '\n#------ SEARCH' + '-' * 80
    for i in a.search_people('*'):
        print '  %s' % i[0]

    print '\n#------ ADD' + '-' * 80
    print a.add_people(**user_dict)

    print '\n#------ MODIFY' + '-' * 80
    print a.modify_people(name, {'gidNumber':'1001'})

    print '\n#------ MODIFY' + '-' * 80
    print a.modify_people(name, {'userPassword': makeSecret('abc123')})

    print '\n#------ SEARCH' + '-' * 80
    for i in a.search_people('*'):
        print '  %s' % i[0]

    print '\n#------ DELETE' + '-' * 80
    print a.delete_people(name)

def test_group(a):

    name       = 'group01'
    group_dict = { 'cn'         : name   ,
                   'gidNumber'  : '9999' ,}

    print '\n#=== GROUP' + '=' * 80
    print '\n#------ SEARCH' + '-' * 80
    for i in a.search_group('*'):
        print '  %s' % i[0]

    print '\n#------ ADD' + '-' * 80
    print a.add_group(**group_dict)

    print '\n#------ MODIFY' + '-' * 80
    print a.modify_group(name, {'gidNumber':'1001'})

    print '\n#------ SEARCH' + '-' * 80
    for i in a.search_group('*'):
        print '  %s' % i[0]

    print '\n#------ DELETE' + '-' * 80
    print a.delete_group(name)

if __name__ == '__main__' : 
    test()
