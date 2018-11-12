import ldap
import ldap.modlist as modlist

server  = '10.11.12.9:389'
user_dn = 'Administrator@myadserver.com'
user_pw = 'Zhu88jie'

#fs_dn = 'cn=usergroupdemo1,ou=Demo,dc=myadserver,dc=com'
fs_dn = 'CN=usergroupdemo1,OU=Demo,DC=myadserver,DC=com'

l = ldap.initialize("ldap://"+server)
ldap.set_option(ldap.OPT_X_TLS_REQUIRE_CERT, ldap.OPT_X_TLS_NEVER)
l.protocol_version = 3
l.set_option(ldap.OPT_REFERRALS, 0)
l.bind_s(user_dn, user_pw)

old_desc = 'usergroupdemo1'
old = {}
old['description'] = old_desc

new_desc = 'usergroupdemo2'
new = {}
new['description'] =new_desc

ldif = modlist.modifyModlist(old, new)
print fs_dn
print "ldif=%s" % ldif
print(l.modify_s(fs_dn,ldif))

l.unbind_s()
