import ldap
import uuid
from ldap.controls import SimplePagedResultsControl

PAGE_SIZE = 500 
pg_ctrl = SimplePagedResultsControl(True, size=PAGE_SIZE, cookie="")
ATTRLIST = ['ou', 'description']
userdata = []


def search():
    server = '10.11.12.9:389'
    user_dn = 'Administrator@myadserver.com'
    user_pw = 'Zhu88jie'
    fs_dn = 'OU=vdi,DC=myadserver,DC=com'
    l = ldap.initialize("ldap://" + server)
    l.bind_s(user_dn, user_pw)
    
    while True:
        msgid = l.search_ext(fs_dn,ldap.SCOPE_ONELEVEL,"(objectClass=user)", ATTRLIST,serverctrls=[pg_ctrl])
        _a, res_data, _b, srv_ctrls = l.result3(msgid)
        print 'res_data', len(res_data)
        userdata.extend(res_data)
        cookie = srv_ctrls[0].cookie
        if cookie:
            pg_ctrl.cookie = cookie
        else:
            break
    print "total: %d" % len(userdata)

search()
