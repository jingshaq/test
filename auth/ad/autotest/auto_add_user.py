'''
Created on 2015-10-02

@author: yunify
'''

import ldap
import ldap.modlist as modlist

def auto_create_user(firstname, lastname, username, ou):
    l = ldap.initialize('ldap://10.11.12.9:389')
    l.simple_bind_s('Administrator@myadserver.com', 'Zhu88jie')
    cn = firstname + ' ' + lastname
    addDN = "cn=%s,%s" % (cn,ou)
    attrs = {}
    attrs['objectclass'] = ['top', 'person', 'organizationalPerson', 'user']
    attrs['cn'] = cn
    attrs['givenName'] = firstname
    attrs['userPassword'] = 'Zhu88jie'
    attrs['description'] = 'add'
    attrs['sn'] = lastname
    user['sAMAccountName'] = username
    user['userPrincipalName'] = '%s@myadserver.com' %(username)
    user['userAccountControl'] = '66048'
    ldif = modlist.addModlist(attrs)
    ret = l.add_s(addDN, ldif)
    l.unbind_s()
    print ret

i=0
j=0
k=0

firstname = 'F'
lastname = 'L'
username = 'U'
for i in range(50):
    base_ou="ou=ou-%d,ou=vdi,dc=myadserver,dc=com" % (i)
    print base_ou
    for j in range(100):
        ou = "ou=ou-%d-%d,%s" % (i,j,base_ou)
        print ou
        for k in range(100):
            auto_create_user("%s%d%d%d"%(firstname,i,j,k),
                    "%s%d%d%d"%(lastname,i,j,k),"%s%d%d%d"%(username,i,j,k), ou)
            
