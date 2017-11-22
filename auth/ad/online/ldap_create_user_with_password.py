'''
Created on 2017-4-14

@author: abel
'''
import ldap
import ldap.modlist as modlist
import sys

def create_ad_user(username, password):
    ldap.set_option(ldap.OPT_X_TLS_REQUIRE_CERT, ldap.OPT_X_TLS_NEVER)
    print '-----------1'
    l = ldap.initialize("ldaps://DC.myadserver.com:636")
    print '-----------2'
    print l.simple_bind_s('Administrator', 'Zhu88jie')
    print '-----------3'

    addDN = "cn=%s,ou=ou1,dc=myadserver,dc=com" % username
    attrs = {}
    attrs['objectclass'] = ['top', 'person', 'organizationalPerson', 'user']
    attrs['cn'] = username
    attrs['userPrincipalName'] = '%s@myadserver.com'%username
    unicode_pass = unicode('\"' + str(password) + '\"', 'iso-8859-1')
    password_value = unicode_pass.encode('utf-16-le')
    attrs['unicodePwd'] = password_value 
    attrs['userAccountControl'] = '66048'
    ldif = modlist.addModlist(attrs)
    print ldif
    ret = l.add_s(addDN, ldif)
    
    l.unbind_s()
    print ret
    
    
create_ad_user('user02', 'Zhu88jie')


