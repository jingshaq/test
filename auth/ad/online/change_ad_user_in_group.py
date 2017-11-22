import ldap

server  = '139.198.6.147:389'
user_dn = 'Administrator'
user_pw = 'Zhu88jie'

fs_dn = 'ou=ou1,dc=myadserver,dc=com'

l = ldap.initialize("ldap://"+server)
print l.bind_s(user_dn, user_pw)
dn = 'CN=user01,OU=ou1,DC=myadserver,DC=com'
newou = 'OU=org1,DC=myadserver,DC=com'

print l.rename_s(dn, 'CN=user01', newou)
l.unbind_s()
