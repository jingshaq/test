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
    newpassword = 'Zhu88jie2'
    oldpassword = 'Zhu88jie1'
    newpassword = unicode('\"' + newpassword + '\"').encode('utf-16-le')
    oldpassword = unicode('\"' + oldpassword + '\"').encode('utf-16-le')
    print oldpassword
    print newpassword
    pass_mod = [(ldap.MOD_DELETE, 'unicodePwd', [oldpassword]), (ldap.MOD_REPLACE, 'unicodePwd', [newpassword])]
    print l.modify_s(user_dn, pass_mod)

    # Its nice to the server to disconnect and free resources when done
    l.unbind_s()

resetPassword('CN=user01,OU=ou1,DC=myadserver,DC=com','Zhu88jie1')
