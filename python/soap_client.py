from soap import HelloWorldService  
  
def make_client():  
    from soaplib.client import make_service_client  
    client = make_service_client('http://172.31.102.14:12000?wsdl', HelloWorldService())  
    return client     
a = make_client()      
print a.says('hello,world')  
