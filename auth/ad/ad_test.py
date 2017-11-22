'''
Created on 2015-10-02

@author: yunify
'''

import ldap


def test_ad_server():
    l = ldap.initialize('ldap://172.16.1.163:389')
    l.protocol_version = 3
    l.set_option(ldap.OPT_REFERRALS, 0)
    print '----------1'
    l.simple_bind_s('Administrator', 'Zhu88jie1')
    ret = l.search_s('dc=testad,dc=com', ldap.SCOPE_SUBTREE)
    print '----------2'
    print ret

def test_ad_search_user(username):
    l = ldap.initialize('ldap://172.16.1.163:389')
    l.simple_bind_s('Administrator', 'Zhu88jie1')
    try:
        searchScope = ldap.SCOPE_SUBTREE
        searchFilter = "userPrincipalName=*" + username + "*"
        print '-----------------------1'
        resultID = l.search(
            'ou=org1,dc=testad,dc=com', searchScope, searchFilter, None)
        print '-----------------------2'
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

def test_ad_create_user(firstname, lastname, username):
    l = ldap.initialize('ldap://172.16.1.163:389')
    l.simple_bind_s('Administrator', 'Zhu88jie1')
    cn = firstname + ' ' + lastname
    addDN = "cn=%s,ou=org1,dc=testad,dc=com" % cn
    attrs = {}
    attrs['objectclass'] = ['top', 'person', 'inetOrgPerson']
    attrs['cn'] = cn
    attrs['givenName'] = firstname
    attrs['userPassword'] = 'Zhu88jie1'
    attrs['description'] = 'add'
    attrs['sn'] = lastname
    ldif = ldap.addModlist(attrs)
    ret = l.add_s(addDN, ldif)
    l.unbind_s()
    print ret

def test_ad_modify_user(firstname, lastname, username):
    l = ldap.initialize('ldap://172.16.1.163:389')
    l.simple_bind_s('Administrator', 'Zhu88jie1')
    cn = firstname + ' ' + lastname
    addDN = "cn=%s,ou=org1,dc=testad,dc=com" % cn
    old = {'description': 'add'}
    new = {'description': 'modify'}
    ldif = ldap.modifyModlist(old, new)
    print ldif
    ret = l.modify_s(addDN, ldif)
    l.unbind_s()
    print ret

def test_ad_delete_user(firstname, lastname, username):
    l = ldap.initialize('ldap://172.16.1.163:389')
    l.simple_bind_s('Administrator', 'Zhu88jie1')
    cn = firstname + ' ' + lastname
    delDN = "cn=%s,ou=org1,dc=testad,dc=com" % cn
    ret = l.delete_s(delDN)
    l.unbind_s()
    print ret

def test_ad_add_ou(ou):
    l = ldap.initialize('ldap://172.16.1.163:389')
    l.simple_bind_s('Administrator', 'Zhu88jie1')
    addDN = "ou=org1,dc=testad,dc=com"
    attrs = {}
    attrs['objectclass'] = ['top']
    ldif = ldap.addModlist(attrs)
    ret = l.add_s(addDN, ldif)
    l.unbind_s()
    print ret
    
def test_ad_search_ou():
    server = '172.16.1.163:389'
    user_dn = 'Administrator'
    user_pw = 'Zhu88jie'
    fs_dn = 'OU=org1,DC=testad,DC=com'
    l = ldap.initialize("ldap://" + server)
    l.bind_s(user_dn, user_pw)
    
    row_ldif_list = l.search_s(fs_dn, ldap.SCOPE_SUBTREE)  
    
    for dn, entry in row_ldif_list:
        print("dn=%s" % dn)
        for _key, _value in entry.items():
            print "%s==>%s" % (_key, _value)
        print '---------------------------'
    
def test_ad_modify_password():
    l = ldap.initialize('ldap://172.16.1.163:389')
    l.bind_s('Administrator', 'Zhu88jie1')
    dn = "CN=user01,OU=ou1,DC=testad,DC=com"
    print '--------------'
    ret = l.passwd(dn, oldpw='Zhu88jie1', newpw='Zhu88jie1')
    print ret
    l.unbind_s()
    
#test_ad_modify_password()

#test_ad_server()

# print '-----------------------------------------------------'
# print test_ad_search_user('user02')

# print '-----------------------------------------------------'
# test_ad_create_user('super','man', 'superman')
# print '-----------------------------------------------------'
# test_ad_search_user('superman')

# print '-----------------------------------------------------'
# test_ad_modify_user('super','man', 'superman')
# print '-----------------------------------------------------'
# test_ad_search_user('superman')

# print '-----------------------------------------------------'
# test_ad_delete_user('super','man', 'superman')
# print '-----------------------------------------------------'
# test_ad_search_user('superman')

#print '-----------------------------------------------------'
#test_ad_add_ou('org1')

#print '-----------------------------------------------------'
#test_ad_search_ou()
#test_ad_modify_password()

def create_ad_user(username, password):
    l = ldap.initialize('ldap://172.16.1.163:389')
    l.simple_bind_s('Administrator', 'Zhu88jie1')
    cn = username
    addDN = "cn=%s,ou=ou1,dc=testad,dc=com" % cn
    attrs = {}
    attrs['objectclass'] = ['top', 'person', 'organizationalPerson', 'user']
    attrs['cn'] = cn
    attrs['userPrincipalName'] = '%s@testad.com'%username
    attrs['userPassword'] = password
    #attrs['clearTextPassword'] = password
    #attrs['unicodePwd'] = unicode('\"' + password + '\"').encode('utf-16-le')
    attrs['userAccountControl'] = '66080'
    #attrs['pwdLastSet'] = '-1'
    ldif = ldap.addModlist(attrs)
    ret = l.add_s(addDN, ldif)
    
    # Prep the password
    #unicode_pass = unicode('\"' + password + '\"', 'iso-8859-1')
    #password_value = unicode_pass.encode('utf-16-le')
    #add_pass = [(ldap.MOD_REPLACE, 'unicodePwd', [password_value])]
    #l.modify_s(addDN, add_pass)
    
    l.unbind_s()
    print ret
    
    
def login_ad_user(username, password):
    l = ldap.initialize('ldap://172.16.1.163:389')
    l.bind_s(username, password)
    print '------1'
    try:
        ret = l.search_s("ou=ou1,dc=testad,dc=com", ldap.SCOPE_SUBTREE, "(userPrincipalName=%s)" % username, ["userPrincipalName"])
    except Exception,e:
        print e
    print '------2'
    if ret is None or len(ret) == 0:
        print("login error")
    else:
        print("login success")
    l.unbind_s()

create_ad_user('user01', 'Zhu88jie1')
#test_ad_modify_password()
#reset_ad_user_password('user01', 'Zhu88jie1')
#login_ad_user('user01@testad.com', 'Zhu88jie1')


