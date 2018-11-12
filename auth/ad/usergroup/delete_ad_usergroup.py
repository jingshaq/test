import ldap

server = '10.11.12.9:389'
user_dn = 'Administrator@myadserver.com'
user_pw = 'Zhu88jie'

fs_dn = 'cn=usergroupdemo1,ou=Demo,dc=myadserver,dc=com'

l = ldap.initialize("ldap://" + server)
l.bind_s(user_dn, user_pw)
print('---------------------')
retcode,_,_,_ = l.delete_s(fs_dn)
print retcode
print('---------------------')
l.unbind_s()
