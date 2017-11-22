import ldap

server  = '172.16.1.163:389'
user_dn = 'Administrator'
user_pw = 'Zhu88jie'

fs_dn = 'ou=ou1,dc=testad,dc=com'

l = ldap.initialize("ldap://"+server)
l.bind_s(user_dn, user_pw)

groupname = 'ou1'

attr = {'objectClass': ['organizationalUnit','top']}

#attr['o'] = groupname
attr['name'] = groupname

ldif = ldap.addModlist(attr)
print fs_dn
print ldif
print('-------------')
retcode, _ = l.add_s(fs_dn,ldif)
print retcode
print _
print('-------------')
l.unbind_s()
