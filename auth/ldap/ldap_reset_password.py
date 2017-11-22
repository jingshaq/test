'''
Created on 2015-10-02

@author: yunify
'''

import ldap

def ldap_reset_password(user_dn, password):
    l = ldap.initialize('ldap://172.16.1.215:389')
    print l.simple_bind_s("cn=manager,dc=centos7,dc=com","zhu88jie")
    print l.passwd_s(user_dn, None, password)
    l.unbind_s()

ldap_reset_password('cn=user01,ou=People,dc=centos7,dc=com', 'Abc123')

