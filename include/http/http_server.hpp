#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <iostream>

#include "request.h"
#include "message_queue.hpp"

class HttpServer {
private:
    MessageQueue<Request> &request_queue;

    auto requestHandler() -> void;
    // TODO: thread pool
public:
    auto start() -> void;

    explicit HttpServer(MessageQueue<Request> &queue);
};

#endif