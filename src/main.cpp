#include <iostream>
#include <thread>

#include "http_server.hpp"

#include "request.h"
#include "message_queue.hpp"
#include "request_sender.h"

auto main(int argc, char *argv[]) -> int {
    std::cout << "usage: new sync <original path> <target path>" << std::endl;
    MessageQueue<Request> local_request_queue;
    LocalRequestSender localRequestSender(local_request_queue);
    HttpServer httpServer(local_request_queue);
    std::thread stdinListener{&LocalRequestSender::start, &localRequestSender};
    std::thread Server{&HttpServer::start, &httpServer};
    stdinListener.join();
    Server.join();
    return 0;
}
