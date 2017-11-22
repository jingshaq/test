import ldap

server  = 'ldap://172.16.1.215:389'
l = ldap.initialize(server)
print l.simple_bind_s("cn=manager,dc=centos7,dc=com","zhu88jie")

dn = 'CN=user01,OU=ou1,dc=centos7,dc=com'
newou = 'OU=People,dc=centos7,dc=com'

print l.rename_s(dn, 'CN=user01', newou)
l.unbind_s()