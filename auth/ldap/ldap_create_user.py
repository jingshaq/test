'''
Created on 2015-10-02

@author: yunify
'''

import ldap

def ldap_create_user(username, password):
    l = ldap.initialize('ldap://172.16.1.215:389')
    l.simple_bind_s("cn=manager,dc=centos7,dc=com","zhu88jie")
    
    addDN = "cn=%s,ou=People,dc=centos7,dc=com" % username
    attrs = {}
    attrs['objectclass'] = ['top','person','inetOrgPerson']
    attrs['cn'] = username
    attrs['userPassword'] = password
    attrs['displayName'] = username
    attrs['description'] = 'User object for replication using slurpd'
    attrs['physicalDeliveryOfficeName'] = 'Beijing Office'
    attrs['title'] = 'CEO'
    attrs['mail'] = 'abc@abc.com'
    attrs['telephoneNumber'] = '13800138000'
    attrs['homePhone'] = '010-12345678'
    
    attrs['sn'] = username
    ldif = ldap.addModlist(attrs)
    print ldif
    print l.add_s(addDN, ldif)
    l.unbind_s()

ldap_create_user('user01', 'Zhu88jie')

