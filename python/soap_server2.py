import soaplib
 
from soaplib.core.service import rpc
from soaplib.core.service import DefinitionBase
from soaplib.core.model.primitive import String, Integer
 
from soaplib.core.server import wsgi
from soaplib.core.model.clazz import Array
 
'''
This is a simple HelloWorld example to show the basics of writing
a webservice using soaplib, starting a server, and creating a service
client.
'''
 
class HelloWorldService(DefinitionBase):
    @rpc(String, _returns=String)
    def hello(self, name):
        '''
        Docstrings for service methods appear as documentation in the wsdl
        <b>what fun</b>
        @param name the name to say hello to
        @param the number of times to say hello
        @return the completed array
        '''
        return  'Hello, %s' % name
 
if __name__=='__main__':
    try:
        from wsgiref.simple_server import make_server
        soap_application = soaplib.core.Application([HelloWorldService], 'tns')
        wsgi_application = wsgi.Application(soap_application)
 
        print "listening to http://0.0.0.0:8080"
        print "wsdl is at: http://127.0.0.1:8080/?wsdl"
 
        server = make_server('0.0.0.0',8080, wsgi_application)
        server.serve_forever()
 
    except ImportError:
        print "Error: example server code requires Python >= 2.5"

