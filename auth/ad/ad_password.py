'''
Created on 2017-4-14

@author: abel
'''
import ldap
import sys
import ldap.modlist as modlist
import os

def reset_ad_user_password(username, password):
    PASSWORD_ATTR = "unicodePwd"
    user_dn = "CN=user01,OU=ou1,DC=testad,DC=com"
    add_pass = password
    '''
    # Set AD password
    unicode_pass = unicode('"%s"'% password, "iso-8859-1")
    print("-------------unicode_pass:%s" % unicode_pass)
    password_value = unicode_pass.encode("utf-16-le")
    print("-------------password_value:%s" % password_value)
    add_pass = [(ldap.MOD_REPLACE, PASSWORD_ATTR, [password_value])]
    print("-------------add_pass:%s" % add_pass)
    '''

    # Replace password
    try:
        l = ldap.initialize('ldap://172.16.1.163:389')
        l.bind_s('Administrator', 'Zhu88jie1')
        print '----------1'
        l.modify(user_dn, add_pass)
        print '----------2'
        print "Active Directory password for", username, \
            "was set successfully!"
    except ldap.LDAPError, e:
        sys.stderr.write('Error setting AD password for: ' + username + '\n')
        sys.stderr.write('Message: ' + str(e) + '\n')
        l.unbind_s()
        sys.exit(1)

def modify_password():
    ld = ldap.initialize('ldap://172.16.1.163:389')
    ld.simple_bind_s('Administrator', 'Zhu88jie1')
    print '1111111111111'
    newpassword = 'Zhu88jie2'
    oldpassword = 'Zhu88jie1'
    newpassword = unicode('\"' + newpassword + '\"').encode('utf-16-le')
    oldpassword = unicode('\"' + oldpassword + '\"').encode('utf-16-le')
    pass_mod = [(ldap.MOD_DELETE, 'unicodePwd', [oldpassword]), (ldap.MOD_ADD, 'unicodePwd', [newpassword])]
    print ld.modify('CN=user01,OU=ou1,DC=testad,DC=com', pass_mod)
    
def modify_password1():
    ld = ldap.initialize('ldap://172.16.1.163:389')
    ld.simple_bind_s('Administrator', 'Zhu88jie1')
    print '1111111111111'
    newpassword = 'Zhu88jie2'
    newpassword = unicode('\"' + newpassword + '\"').encode('utf-16-le')
    pass_mod = [(ldap.MOD_REPLACE, 'unicodePwd', [newpassword])]
    print  ld.modify('CN=user01,OU=ou1,DC=testad,DC=com', pass_mod)

def modify_password2():
    ld = ldap.initialize('ldap://172.16.1.163:389')
    ld.simple_bind('Administrator', 'Zhu88jie1')
    dn = 'CN=user01,OU=ou1,DC=testad,DC=com'
    print '1111111111111'
    old_value = {"userPassword": ["Zhu88jie1"]}
    new_value = {"userPassword": ["Zhu88jie2"]}

    modlist = ldap.modlist.modifyModlist(old_value, new_value)
    print ld.modify_s(dn, modlist)

def modify_password3():
    ld = ldap.initialize('ldap://172.16.1.163:389')
    print ld.simple_bind_s('user01@testad.com', 'Zhu88jie1')
    dn = 'CN=user01,OU=ou1,DC=testad,DC=com'
    print ld.passwd(dn, None, 'Zhu88jie2')
    
def modify_password4():
    ld = ldap.initialize('ldap://172.16.1.163:389')
    print ld.simple_bind_s('user01@testad.com', 'Zhu88jie1')
    dn = 'CN=user01,OU=ou1,DC=testad,DC=com'
    password = [(ldap.MOD_REPLACE, 'userPassword', ['Zhu88jie2'])]
    print  ld.modify('CN=user01,OU=ou1,DC=testad,DC=com', password)

def modify_password5():
    l = ldap.initialize('ldap://172.16.1.163:389')
    print l.simple_bind_s('user01@testad.com', 'Zhu88jie1')
    dn = 'CN=user01,OU=ou1,DC=testad,DC=com'
    print l.passwd(dn, 'Zhu88jie1', 'Zhu88jie2')
    l.unbind_s()
    
def modify_password6():
    l = ldap.initialize('ldap://172.16.1.163:389')
    print l.simple_bind_s('user01@testad.com', 'Zhu88jie1')
    dn = 'CN=user01,OU=ou1,DC=testad,DC=com'
    print l.passwd(dn, 'Zhu88jie1', 'Zhu88jie2')
    l.unbind_s()

def changePassword(user_dn, old_password, new_password):
    ldap.set_option(ldap.OPT_X_TLS_REQUIRE_CERT, ldap.OPT_X_TLS_NEVER)
    print '-----------1'
    l = ldap.initialize("ldaps://DC.testad.com:636")
    print '-----------2'
    l.set_option(ldap.OPT_REFERRALS,0)
    print '-----------3'
    l.set_option(ldap.OPT_PROTOCOL_VERSION,3)
    print '-----------3.1'
    cafile = os.getcwd()+"/certnew.cer"
    print cafile
    l.set_option(ldap.OPT_X_TLS_CACERTFILE, cafile)
    print '-----------4'
    l.set_option(ldap.OPT_X_TLS,ldap.OPT_X_TLS_DEMAND)
    print '-----------5'
    l.set_option(ldap.OPT_X_TLS_DEMAND,True)
    print '-----------6'
    l.set_option(ldap.OPT_DEBUG_LEVEL,255)
    print '-----------7'
    l.start_tls_s()
    print '-----------8'
    print l.bind_s('Administrator', 'Zhu88jie1')
    #print l.simple_bind_s('user01@testad.com', 'Zhu88jie1')
    

    # Reset Password
    unicode_pass = unicode('\"' + str(new_password) + '\"', 'iso-8859-1')
    password_value = unicode_pass.encode('utf-16-le')
    add_pass = [(ldap.MOD_REPLACE, 'unicodePwd', [password_value])]

    l.modify_s(user_dn,add_pass)

    # Its nice to the server to disconnect and free resources when done
    l.unbind_s()
changePassword('CN=user01,OU=ou1,DC=testad,DC=com', 'Zhu88jie1', 'Zhu88jie2')
