#include <iostream>
#include <string>
#include <thread>
#include <zmq.hpp>

#include "message.pb.h"

int main() {
    using namespace std::chrono_literals;

    // initialize the zmq context with a single IO thread
    zmq::context_t context{1};

    // construct a REP (response) socket and bind to interface
    zmq::socket_t socket{context, zmq::socket_type::rep};
    socket.bind("tcp://*:5555");

    for (;;) {
        zmq::message_t request;

        // receive a request from client
        socket.recv(request, zmq::recv_flags::none);

        message::v1::Message requestMsg;
        requestMsg.ParseFromArray(request.data(), request.size());
        std::cout << "Received " << requestMsg.info() << " from " << requestMsg.who() << std::endl;

        // simulate work
        std::this_thread::sleep_for(1s);

        // send the response to the client
        // prepare some static data for responses
        message::v1::Message response;
        response.set_who("Bob");
        response.set_info("Welcome");
        std::string serializedResponse = response.SerializeAsString();
        socket.send(zmq::buffer(serializedResponse), zmq::send_flags::none);
    }

    return 0;
}
