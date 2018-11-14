'''
Created on 2015-10-02

@author: yunify
'''
import traceback
import ldap
import ldap.modlist as modlist

def auto_create_user(username, ou):
    conn_s = ldap.initialize("ldap://10.11.12.9:389")
    conn_s.simple_bind_s('Administrator@myadserver.com', 'Zhu88jie')
    cn = username
    addDN = "cn=%s,%s" % (cn,ou)
    attrs = {}
    attrs['objectclass'] = ['top', 'person', 'organizationalPerson', 'user']
    attrs['cn'] = cn
    attrs['displayName'] = username
    attrs['givenName'] = username
    attrs['description'] = 'add'
    attrs['sAMAccountName'] = username
    attrs['userPrincipalName'] = '%s@myadserver.com' %(username)
    ldif = modlist.addModlist(attrs)
    ret = conn_s.add_s(addDN, ldif)
    conn_s.unbind_s()

i=0
j=0
k=0
username = 'auto'
for i in range(100):
    auto_create_user("%s%d"%(username,i), "ou=vdi,dc=myadserver,dc=com")

for i in range(20):
    base_ou="ou=ou-%d,ou=vdi,dc=myadserver,dc=com" % (i)
    for j in range(10):
        ou = "ou=ou-%d-%d,%s" % (i,j,base_ou)
        for k in range(10):
            auto_create_user("%s%d%d%d"%(username,i,j,k),ou)
