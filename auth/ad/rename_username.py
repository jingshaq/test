import ldap
import ldap.modlist as modlist

server  = '10.11.12.9:389'
user_dn = 'Administrator@myadserver.com'
user_pw = 'Zhu88jie'

fs_dn = 'cn=test99,ou=temp0,dc=myadserver,dc=com'

l = ldap.initialize("ldap://"+server)
ldap.set_option(ldap.OPT_X_TLS_REQUIRE_CERT, ldap.OPT_X_TLS_NEVER)
l.protocol_version = 3
l.set_option(ldap.OPT_REFERRALS, 0)
l.bind_s(user_dn, user_pw)

new_dn = 'OU=temp0,DC=myadserver,DC=com'


print(l.rename_s(fs_dn, "cn=test999", new_dn))

l.unbind_s()
