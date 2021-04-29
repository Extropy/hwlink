#!/bin/python
import helloworld_pb2
from coapthon.client.helperclient import HelperClient
import sys

m = helloworld_pb2.sayhello()
m.greeting = "Hello, proto-world"
m.n = 5

print(m)
f = open("hellotest.dat","wb")
f.write(m.SerializeToString())
f.close()
print("Stored ",m)

m2 = helloworld_pb2.sayhello()
f = open("hellotest.dat","rb")
m2.ParseFromString(f.read())
f.close()
print("Recovered ",m2)

#c = HelperClient(server=('127.0.1.1',5683))
#r = c.get("basic")
#r.prettyprint()
#c.stop()

