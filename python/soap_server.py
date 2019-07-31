import soaplib
from soaplib.service import soapmethod  
from soaplib.serializers.primitive import String, Integer, Array  
from soaplib.wsgi_soap import SimpleWSGISoapApp  
     
class HelloWorldService(SimpleWSGISoapApp):  
    @soapmethod(String, _returns=String)  
    def says(self,name):       
        return '{"name":"%s"}' % name  
  
  
if __name__=='__main__':  
  
    try:  
        from wsgiref.simple_server import make_server  
        server = make_server('0.0.0.0', 12000, HelloWorldService())  
        print "listening on 0.0.0.0:12000"  
        server.serve_forever()  
    except ImportError:  
        print "Error: example server code requires Python >= 2.5"  
