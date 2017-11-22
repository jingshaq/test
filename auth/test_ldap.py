'''
Created on 2015-10-02

@author: yunify
'''

import login_server_auth as auth
import ldap


def test_ldap_server():
    l = ldap.initialize('ldap://172.16.1.215:389')
    ret = l.search_s('dc=centos7,dc=com',ldap.SCOPE_SUBTREE)
    print ret

def test_ldap_search_user(username):
    l = ldap.initialize('ldap://172.16.1.215:389')
    try:
        searchScope = ldap.SCOPE_SUBTREE
        searchFilter = "uid=*" + username + "*"
        resultID = l.search('ou=People,dc=centos7,dc=com', searchScope, searchFilter, None)
        result_set = []
        while 1:
            result_type, result_data = l.result(resultID, 0)
            print "result_data = %s" % result_data
            print "RES_SEARCH_ENTRY = %d" % ldap.RES_SEARCH_ENTRY
            print "result_type = %d" % result_type
            if (result_data == []):
                break
            else:
                if result_type == ldap.RES_SEARCH_ENTRY:
                    result_set.append(result_data)
        return result_set[0][0][1]['cn'][0]
    except ldap.LDAPError, e:
        print e


def test_ldap_create_user(firstname, lastname, username):
    l = ldap.initialize('ldap://172.16.1.215:389')
    l.simple_bind_s("cn=manager,dc=centos7,dc=com","zhu88jie")
    cn = firstname + ' ' + lastname
    addDN = "cn=%s,ou=People,dc=centos7,dc=com" % cn
    attrs = {}
    attrs['objectclass'] = ['top','person','inetOrgPerson']
    attrs['cn'] = cn
    attrs['givenName'] = firstname
    attrs['userPassword'] = 'zhu88jie'
    attrs['description'] = 'User object for replication using slurpd'
    attrs['sn'] = lastname
    attrs['uid'] = username
    ldif = ldap.addModlist(attrs)
    ret = l.add_s(addDN, ldif)
    l.unbind_s()
    print ret

def test_ldap_modify_user(firstname, lastname, username):
    l = ldap.initialize('ldap://172.16.1.215:389')
    l.simple_bind_s("cn=manager,dc=centos7,dc=com","zhu88jie")
    cn = firstname + ' ' + lastname
    addDN = "cn=%s,ou=People,dc=centos7,dc=com" % cn
    old = {'description':'User object for replication using slurpd'}
    new = {'description':'modify success'}
    ldif = ldap.modifyModlist(old, new)
    print ldif
    ret = l.modify_s(addDN, ldif)
    l.unbind_s()
    print ret

def test():
    auth_ldap = auth.LDAPLoginServerAuth("172.16.1.215", "dc=centos7,dc=com")
    ret = auth_ldap.login('abel', 'zhu88jie')
    print ret

def test_ldap_delete_user(firstname, lastname, username):
    l = ldap.initialize('ldap://172.16.1.215:389')
    l.simple_bind_s("cn=manager,dc=centos7,dc=com","zhu88jie")
    cn = firstname + ' ' + lastname
    delDN = "cn=%s,ou=People,dc=centos7,dc=com" % cn
    ret = l.delete_s(delDN)
    l.unbind_s()
    print ret


test_ldap_server()

#print '-----------------------------------------------------'
#test_ldap_create_user('super','man', 'superman')

#print '-----------------------------------------------------'
#test_ldap_search_user('superman')

#print '-----------------------------------------------------'
#test_ldap_modify_user('super','man', 'superman')

#print '-----------------------------------------------------'
#test_ldap_search_user('superman')

#print '-----------------------------------------------------'
#test_ldap_delete_user('super','man', 'superman')

#print '-----------------------------------------------------'
#test_ldap_search_user('superman')

