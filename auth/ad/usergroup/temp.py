import ldap
import uuid

def search():
    server = '10.11.12.9:389'
    user_dn = 'Administrator@myadserver.com'
    user_pw = 'Zhu88jie'
    fs_dn = 'OU=Demo,DC=myadserver,DC=com'
    l = ldap.initialize("ldap://" + server)
    l.bind_s(user_dn, user_pw)

    filterstr="(objectclass=user)"
    #filterstr="(&(objectclass=user)(memberOf='OU=Demo,DC=myadserver,DC=com'))"
    row_ldif_list = l.search_s(fs_dn, ldap.SCOPE_SUBTREE, filterstr=filterstr)  
    #row_ldif_list = l.search_s(fs_dn, ldap.SCOPE_SUBTREE,filterstr='(objectclass=group)')  
    
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
