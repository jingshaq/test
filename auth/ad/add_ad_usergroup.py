import ldap

server  = '172.16.1.163:389'
user_dn = 'Administrator'
user_pw = 'Zhu88jie'

fs_dn = 'cn=ug1,ou=ou1,o=org3,dc=testad,dc=com'

l = ldap.initialize("ldap://"+server)
l.bind_s(user_dn, user_pw)

groupname = 'ug1'

attr = {}
attr['objectClass'] = ['group','top']
attr['cn'] = groupname
attr['name'] = groupname
attr['sAMAccountName'] = groupname

ldif = ldap.addModlist(attr)
print fs_dn
print ldif
print(l.add_s(fs_dn,ldif))
l.unbind_s()
