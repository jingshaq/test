'''
Created on 2015-10-02

@author: yunify
'''

import ldap

def ldap_login(username, user_dn, password):
    l = ldap.initialize('ldap://172.16.1.215:389')
    l.simple_bind_s(user_dn,password)
    
    ret = l.search_s('ou=People,dc=centos7,dc=com', ldap.SCOPE_SUBTREE, "cn=%s" % username)
    if ret is None or len(ret) == 0:
        print 'login error'
    else:
        print ret
        print 'login success'
    l.unbind_s()

ldap_login('user01', 'cn=user01,ou=People,dc=centos7,dc=com', 'Abc123')

