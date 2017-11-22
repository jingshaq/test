'''
Created on 2015-10-02

@author: yunify
'''

import ldap

def ldap_modify_password(user_dn, old_password, new_password):
    l = ldap.initialize('ldap://172.16.1.215:389')
    print l.simple_bind_s(user_dn, old_password)
    print l.passwd_s(user_dn, old_password, new_password)
    l.unbind_s()

ldap_modify_password('cn=user01,ou=People,dc=centos7,dc=com', 'Zhu88jie', 'Zhu88jie1')

