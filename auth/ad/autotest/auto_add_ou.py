import ldap
import ldap.modlist as modlist

server  = '10.11.12.9:389'
user_dn = 'Administrator@myadserver.com'
user_pw = 'Zhu88jie'

fs_dn = 'ou=vdi,dc=myadserver,dc=com'

l = ldap.initialize("ldap://"+server)
l.bind_s(user_dn, user_pw)

groupname = 'ou'
i=0

attr = {'objectClass': ['organizationalUnit','top']}

for i in range(50):
    j=0
    name=groupname+'-%d'%i
    dn="ou=%s,"%name + fs_dn 
    attr['name'] = name
    ldif = modlist.addModlist(attr)
    cur_dn = dn
    l.add_s(cur_dn,ldif)
    for j in range(10):
        name=groupname+'-%d'%i+'-%d'%j
        attr['name'] = name
        ldif = modlist.addModlist(attr)
        dn = "ou=ou-%s-%s," % (i,j) + cur_dn
        l.add_s(dn,ldif)
l.unbind_s()
