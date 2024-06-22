#!/usr/bin/env python3

#   Hello World client in Python
#   Connects REQ socket to tcp://localhost:5555
#   Sends "Hello" to server, expects "World" back

import message_pb2
import zmq

context = zmq.Context()

#  Socket to talk to server
print("Connecting to hello world server…")
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

#  Do 10 requests, waiting each time for a response
for request_index in range(10):
    print(f"Sending request {request_index} …")

    #  Send the request.
    request_message = message_pb2.Message()
    request_message.who = "Alice"
    request_message.info = "Hello"
    serialized_request = request_message.SerializeToString()
    socket.send(serialized_request)

    #  Get the response.
    serialized_response = socket.recv()
    response_message = message_pb2.Message()
    response_message.ParseFromString(serialized_response)

    print(f"Received response {request_index} {response_message.info} from {response_message.who}")
