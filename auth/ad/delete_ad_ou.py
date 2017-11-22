import ldap

server = '172.16.1.163:389'
user_dn = 'Administrator'
user_pw = 'Zhu88jie'

fs_dn = 'ou=ou1,dc=testad,dc=com'

l = ldap.initialize("ldap://" + server)
l.bind_s(user_dn, user_pw)
print('---------------------')
retcode,_,_,_ = l.delete_s(fs_dn)
print retcode
print('---------------------')
l.unbind_s()
