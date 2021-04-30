#!/bin/python
import logging
import asyncio
from aiocoap import *
import helloworld_pb2

logging.basicConfig(level=logging.INFO)
m = helloworld_pb2.sayhello()

async def main():

    context = await Context.create_client_context()

#    await asyncio.sleep(2)

#    payload = b"abc\n"
    request = Message(code=GET, uri="coap://localhost/other/block")

    response = await context.request(request).response

    #print('Result: %s\n%r'%(response.code, response.payload))
    m.ParseFromString(response.payload)
    print("Received ",m)

if __name__ == "__main__":
    asyncio.get_event_loop().run_until_complete(main())
