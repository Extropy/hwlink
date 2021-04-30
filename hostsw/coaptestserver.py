#!/bin/python
import aiocoap.resource as resource
import aiocoap
import helloworld_pb2
import asyncio


class BlockResource(resource.Resource):

    def __init__(self):
        super().__init__()
        m = helloworld_pb2.sayhello()
        m.greeting = "Hello via protocol buffers over coap, world."
        m.n=42
        self.set_content(m.SerializeToString())

    def set_content(self, content):
        self.content = content

    async def render_get(self, request):
        return aiocoap.Message(payload=self.content)

    async def render_put(self, request):
        print('PUT payload: %s' % request.payload)
        self.set_content(request.payload)
        return aiocoap.Message(code=aiocoap.CHANGED, payload=self.content)

        
def main():

    # Resource tree creation
    root = resource.Site()

    root.add_resource(['.well-known', 'core'],resource.WKCResource(root.get_resources_as_linkheader))
    root.add_resource(['other', 'block'], BlockResource())

    asyncio.Task(aiocoap.Context.create_server_context(root))

    asyncio.get_event_loop().run_forever()

if __name__ == '__main__':
    main()
