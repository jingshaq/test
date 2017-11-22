import ldap

def create_ad_user(username, password):
    l = ldap.initialize('ldap://139.198.6.219:389')
    print l.bind_s('Administrator', 'Zhu88jie')
    addDN = "cn=%s,ou=ou1,dc=myadserver,dc=com" % username
    attrs = {}
    attrs['objectclass'] = ['top', 'person', 'organizationalPerson', 'user']
    attrs['cn'] = username
    attrs['userPrincipalName'] = username
    #attrs['userAccountControl'] = '66080'
    ldif = ldap.modlist.addModlist(attrs)
    print ldif
    ret = l.add_s(addDN, ldif)
    
    l.unbind_s()
    print ret
    
    
create_ad_user('user01', 'Zhu88jie')


