'''
Created on 2017-4-14

@author: abel
'''
import ldap
import sys

def resetPassword(user_dn, new_password):
    ldap.set_option(ldap.OPT_X_TLS_REQUIRE_CERT, ldap.OPT_X_TLS_NEVER)
    print '-----------1'
    l = ldap.initialize("ldaps://DC.myadserver.com:636")
    print '-----------2'
    print l.simple_bind_s('Administrator', 'Zhu88jie')
    print '-----------3'

    # Reset Password
    unicode_pass = unicode('\"' + str(new_password) + '\"', 'iso-8859-1')
    password_value = unicode_pass.encode('utf-16-le')
    add_pass = [(ldap.MOD_REPLACE, 'unicodePwd', [password_value]),(ldap.MOD_REPLACE, 'unicodePwd', [password_value])]
    print add_pass
    print l.modify_s(user_dn,add_pass)

    # Its nice to the server to disconnect and free resources when done
    l.unbind_s()

resetPassword('CN=user01,OU=ou1,DC=myadserver,DC=com','Zhu88jie2')
