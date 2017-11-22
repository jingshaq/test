import ldap
import uuid

def search():
    server = '139.198.13.104:389'
    user_dn = 'Administrator'
    user_pw = 'Zhu88jie'
    fs_dn = 'OU=vdi,DC=myadserver,DC=com'
    l = ldap.initialize("ldap://" + server)
    l.bind_s(user_dn, user_pw)
    
    row_ldif_list = l.search_s(fs_dn, ldap.SCOPE_SUBTREE)  
    
    for dn, entry in row_ldif_list:
        print("dn=%s" % dn)
        for _key, _value in entry.items():
            if _key == 'objectGUID':
                uid = uuid.UUID(bytes_le=_value[0])
                print "%s==>%s" % (_key, uid)
            else:
                print "%s==>%s" % (_key, _value)
        print '---------------------------'

search()
