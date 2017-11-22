import ldap
def login_ad_user(username, password):
    l = ldap.initialize('ldap://172.16.1.163:389')
    l.simple_bind_s(username, password)
    print '------1'
    try:
        ret = l.search_s("cn=user01,ou=ou1,dc=testad,dc=com", ldap.SCOPE_SUBTREE, "(userPrincipalName=%s)" % username, ["userPrincipalName"])
        print ret
    except Exception,e:
        print e
    print '------2'
    if ret is None or len(ret) == 0:
        print("login error")
    else:
        print("login success")
    l.unbind_s()

login_ad_user('user01@testad.com', 'Zhu88jie1')
