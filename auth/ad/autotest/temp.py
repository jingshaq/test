'''
Created on 2015-10-02

@author: yunify
'''

import ldap
import ldap.modlist as modlist

def auto_create_user(username, ou):
    ldap.set_option(ldap.OPT_X_TLS_REQUIRE_CERT, ldap.OPT_X_TLS_NEVER)
    conn_s = ldap.ldapobject.ReconnectLDAPObject("ldaps://10.11.12.9:636")
    conn_s.protocol_version = 3
    conn_s.set_option(ldap.OPT_REFERRALS, 0)
    conn_s.simple_bind_s('Administrator@myadserver.com', 'Zhu88jie')
    cn = username
    addDN = "cn=%s,%s" % (cn,ou)
    print addDN
    attrs = {}
    attrs['objectclass'] = ['top', 'person', 'organizationalPerson', 'user']
    attrs['cn'] = cn
    attrs['givenName'] = username
    unicode_password = unicode('\"' + str("Zhu88jie") + '\"', 'iso-8859-1')
    password_value = unicode_password.encode('utf-16-le')
    attrs['unicodePwd'] = password_value
    attrs['description'] = 'add'
    attrs['sAMAccountName'] = username
    attrs['userPrincipalName'] = '%s@myadserver.com' %(username)
    attrs['userAccountControl'] = '66048'
    ldif = modlist.addModlist(attrs)
    ret = conn_s.add_s(addDN, ldif)
    conn_s.unbind_s()
    print ret

auto_create_user("aaa", "ou=vdi,dc=myadserver,dc=com")
