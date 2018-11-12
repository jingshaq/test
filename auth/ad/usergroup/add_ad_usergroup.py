import ldap
import ldap.modlist as modlist

server  = '10.11.12.9:389'
user_dn = 'Administrator@myadserver.com'
user_pw = 'Zhu88jie'


l = ldap.initialize("ldap://"+server)
l.bind_s(user_dn, user_pw)

groupname = 'usergroupdemo1'

fs_dn = 'cn=%s,ou=Demo,dc=myadserver,dc=com' % groupname

attr = {}
attr['objectClass'] = ['group','top']
attr['name'] = groupname
attr['description'] = groupname
#attr['groupType'] = '8' # this is common type

ldif = modlist.addModlist(attr)
print fs_dn
print ldif
print(l.add_s(fs_dn,ldif))
l.unbind_s()
