import ldap

server  = '172.16.1.163:389'
user_dn = 'Administrator'
user_pw = 'Zhu88jie'

fs_dn = 'ou=ou1,dc=testad,dc=com'

l = ldap.initialize("ldap://"+server)
l.bind_s(user_dn, user_pw)

old_groupname = 'ou1'
old = {}
old['description'] = old_groupname

new_groupname = 'ou2'
new = {}
new['description'] = new_groupname


ldif = ldap.modifyModlist(old, new)
print fs_dn
print ldif
print(l.modify_s(fs_dn,ldif))
l.unbind_s()
