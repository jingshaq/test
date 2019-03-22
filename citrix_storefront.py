#!/usr/bin/python
# -*- coding:utf-8 -*-
import requests


class Citrix:
    def __init__(self, host, port=80, base_uri="/Citrix/StoreWeb"):
        self.host = host
        self.port = port
        self.headers = {}
        self.cookies = None
        self.csrf_token = None
        self.ica_file = None
        self.base_url = "http://%s%s" % (host, base_uri)
        if port != 80:
            self.base_url = "%s:%s%s" % (self.base_url, port, base_uri)

    def get_cookie_string(self, cookies={}):
        cookie_str = ""
        if cookies is None or len(cookies) == 0:
            return cookie_str

        for k, v in cookies.items():
            if len(cookie_str) == 0:
                cookie_str = "%s=%s;" % (k, v)
            else:
                cookie_str = cookie_str + "%s=%s;" % (k, v)
        if len(cookie_str) > 0:
            cookie_str = cookie_str[:-1]
        print "cookie_str ========================= %s" % cookie_str
        return cookie_str

    # build request headers
    def build_request_headers(self, uri):
        url = "%s%s" % (self.base_url, uri)

        # build headers
        self.headers = {}
        self.headers["Host"] = self.host
        self.headers["Accept"] = "application/xml, text/xml, */*; q=0.01"
        self.headers["Accept-Language"] = "en-us,en;q=0.7,fr;q=0.3"
        self.headers["Accept-Encoding"] = "gzip, deflate"
        self.headers["X-Requested-With"] = "XMLHttpRequest"
        self.headers["X-Citrix-IsUsingHTTPS"] = "No"
        self.headers["Referer"] = self.base_url + "/"
        self.headers["Connection"] = "keep-alive"
        self.headers["Pragma"] = "no-cache"
        self.headers["Cache-Control"] = "no-cache"
        self.headers["User-Agent"] = "Mozilla/5.0 (X11; Fedora; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36"
        return url

    # print response
    def print_response(self, response):
        print "======================================="
        print "RESPONSE:"
        print "status: %d" % response.status_code
        print "reason: %s" % response.reason
        print "cookies: %s" % response.cookies
        print "text: \n%s" % response.text

    # /Home/KeepAlive
    def keepalive(self):
        url = "%s%s" % (self.base_url, "/Home/KeepAlive")
        print "REQUEST: " + url
        print self.headers
        response = requests.head(url)
        self.print_response(response)

    # /Home/Configuration
    def home_configuration(self):
        url = self.build_request_headers(uri="/Home/Configuration")
        print "REQUEST:" + url
        print self.headers
        response = requests.post(url, headers=self.headers)
        self.print_response(response)

    # /Authentication/GetAuthMethods
    def get_auth_methods(self):
        url = self.build_request_headers(uri="/Authentication/GetAuthMethods")
        print "REQUEST:" + url
        response = requests.post(url, headers=self.headers)
        self.print_response(response)

    # /PostCredentialsAuth/Login
    def post_credentials_auth_login(self, username, password):
        url = self.build_request_headers(uri="/PostCredentialsAuth/Login?username=%s&password=%s" % (username, password))
        print "REQUEST:" + url
        response = requests.post(url, headers=self.headers)
        self.cookies = requests.utils.dict_from_cookiejar(response.cookies)
        self.csrf_token = self.cookies["CsrfToken"]
        print "-=-=-=-=-=--==" + self.csrf_token
        self.print_response(response)

    # /Resources/List
    def resources_list(self):
        url = self.build_request_headers(uri="/Resources/List")
        print "REQUEST:" + url
        self.headers["Accept"] = "application/json, text/javascript, */*; q=0.01"
        self.headers["Content-Type"] = "Content-Type: application/x-www-form-urlencoded; charset=UTF-8"
        self.headers["Csrf-Token"] = self.csrf_token
        cookie_str = self.get_cookie_string(self.cookies)
        print "cookie_str-=-=-=-=-==%s" % cookie_str
        self.headers["Cookie"] = cookie_str
        response = requests.post(url, headers=self.headers)
        # json_text = json.loads(response.text)
        # print json_text["resources"]
        self.print_response(response)

    # /Resources/GetLaunchStatus
    def resources_get_lanch_status(self):
        pass

    # /Resources/LanchIca
    def resources_launch_ica(self):
        url = self.build_request_headers(uri="/Resources/LaunchIca/c2Yua2dnZyAkUDMy.ica")
        url = url + "?CsrfToken="+self.csrf_token
        url = url + "&displayNameDesktopTitle=test-005"
        print "REQUEST:" + url
        cookie_str = self.get_cookie_string(self.cookies)
        print "cookie_str-=-=-=-=-==%s" % cookie_str
        self.headers["Cookie"] = cookie_str

        response = requests.get(url, headers=self.headers)
        self.print_response(response)

if __name__ == "__main__":
    citrix = Citrix(host="10.11.13.27", base_uri="/Citrix/sfWeb")
    citrix.home_configuration()
    print "\n---------------------------------------\n"
    citrix.get_auth_methods()
    print "\n---------------------------------------\n"
    citrix.post_credentials_auth_login('citrix4@myadserver.com', 'Zhu88jie')
    print "\n---------------------------------------\n"
    citrix.resources_list()
    print "\n---------------------------------------\n"
    citrix.resources_launch_ica()
