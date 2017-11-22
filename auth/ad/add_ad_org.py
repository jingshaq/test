import ldap

server  = '172.16.1.163:389'
user_dn = 'Administrator'
user_pw = 'Zhu88jie'

fs_dn = 'o=org,dc=testad,dc=com'

l = ldap.initialize("ldap://"+server)
l.bind_s(user_dn, user_pw)

groupname = 'org3'

attr = {}
attr['objectClass'] = ['organization','top']
#attr['o'] = groupname
attr['name'] = groupname

ldif = ldap.addModlist(attr)
print fs_dn
print ldif
print(l.add_s(fs_dn,ldif))
l.unbind_s()
