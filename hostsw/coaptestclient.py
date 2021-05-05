#!/bin/python
import logging
import asyncio
from aiocoap import *
import helloworld_pb2

logging.basicConfig(level=logging.INFO)
m = helloworld_pb2.sayhello()

async def main():

    m.greeting = "Hello protobuf"
    m.n = 43
    
    context = await Context.create_client_context()
    request = Message(code=GET, uri="coap://10.1.2.99/info",payload="Hello".encode('utf8'))
    response = await context.request(request).response
    print('Result: %s%r\n'%(response.code, response.payload))
    #m.ParseFromString(response.payload)
    #print("Received ",m)

if __name__ == "__main__":
    asyncio.get_event_loop().run_until_complete(main())
