import os
import copy
import ldap
import ldap.modlist as modlist

server  = '10.11.12.9:389'
user_dn = 'Administrator@myadserver.com'
user_pw = 'Zhu88jie'

fs_dn = 'CN=usergroup,OU=Demo,DC=myadserver,DC=com'

l = ldap.initialize("ldap://"+server)
ldap.set_option(ldap.OPT_X_TLS_REQUIRE_CERT, ldap.OPT_X_TLS_NEVER)
l.protocol_version = 3
l.set_option(ldap.OPT_REFERRALS, 0)
l.bind_s(user_dn, user_pw)

row_ldif_list = l.search_s(fs_dn, ldap.SCOPE_SUBTREE, filterstr='(objectclass=group)')  

old_member = None
for dn, entry in row_ldif_list:
    print("dn=%s" % dn)
    for _key, _value in entry.items():
        if _key == 'member':
            print "%s==>%s" % (_key,  _value)
            old_member = _value
            break

old = {}
old['member'] = old_member

new_member = copy.copy(old_member)

print old_member
print new_member
print '----------'

mem1 = "CN=demo3,OU=wuhan,OU=develop,OU=Demo,DC=myadserver,DC=com"
if mem1 in new_member:
    new_member.remove(mem1)
else:
    print "not exist"
    os._exit(0)
print new_member
new = {}
new['member']=new_member

print "old=%s" % old
print "new=%s" % new

ldif = modlist.modifyModlist(old, new)
print fs_dn
print "ldif=%s" % ldif
print(l.modify_s(fs_dn,ldif))

l.unbind_s()
