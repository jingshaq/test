'''
Created on 2015-10-02

@author: yunify
'''

import ldap

class BaseLoginServerAuth(object):
    '''  base login server authentication '''

    def __init__(self, server_host, base_dn, server_port=ldap.PORT):
        self.uri = "ldap://%s:%s" % (server_host, server_port)
        self.basedn = base_dn
        self.conn = None

    def _conn(self):
        if self.conn:
            return self.conn
        conn = ldap.initialize(self.uri)
        conn.protocol_version = 3
        conn.set_option(ldap.OPT_REFERRALS, 0)
        self.conn = conn
        return self.conn


class ADLoginServerAuth(BaseLoginServerAuth):
    ''' windows AD server authentication '''

    def __init__(self, server_host, base_dn, server_port=ldap.PORT):
        super(ADLoginServerAuth, self).__init__(server_host, base_dn, server_port)

    def login(self, auth_user, auth_passwd):
        try:
            # login
            conn = self._conn()
            conn.simple_bind_s(auth_user, auth_passwd)

            # get user info
            ret = conn.search_s(
                self.basedn, ldap.SCOPE_SUBTREE,
                "(userPrincipalName=%s)" % auth_user,
                ["displayName", "userPrincipalName", "objectGUID"])
            if ret is None or len(ret) == 0:
                print("login to server [%s] succeeded but [%s] not found" % (self.uri, auth_user))
                return None
            user = ret[0][1]
            user_info = {'user_name': user['displayName'][0],
                         'email': user['userPrincipalName'][0],
                         'account_id': user['userPrincipalName'][0]}
        except Exception, e:
            print("login to server [%s] for [%s] failed, [%s]" % (self.uri, auth_user, e))
            return None
        finally:
            conn.unbind_s()
        return user_info


class LDAPLoginServerAuth(BaseLoginServerAuth):
    '''linux ldap server authentication'''

    def __init__(self, server_host, base_dn, server_port=ldap.PORT):
        super(LDAPLoginServerAuth, self).__init__(server_host, base_dn, server_port)

    def login(self, auth_user, auth_passwd):
        try:
            # login
            user_name = auth_user.split('@')[0]
            conn = self._conn()
            user_dn = "cn=%s," % user_name + self.basedn
            conn.simple_bind_s(user_dn, auth_passwd)

            # get user info
            ret = conn.search_s(
                self.basedn, ldap.SCOPE_SUBTREE,
                "cn=%s" % user_name)
            if ret is None or len(ret) == 0:
                return None
            user = ret[0][1]
            user_info = {'account_id': auth_user,
                         'user_name': user['givenName'][0],
                         'email': auth_user}
        except Exception, e:
            print("login to server [%s] for [%s] failed, [%s]" % (self.uri, auth_user, e))
            return None
        finally:
            conn.unbind_s()
        return user_info
