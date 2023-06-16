#ifndef REQUEST_SENDER_H
#define REQUEST_SENDER_H

#include <iostream>

#include "request.h"
#include "message_queue.hpp"


class LocalRequestSender {
private:
    MessageQueue<Request> &request_queue;
    std::string input_string;

    auto stdinRead() -> void;

    auto inputParse() -> void;

public:
    auto start() -> void;

    explicit LocalRequestSender(MessageQueue<Request> &queue);
};

#endif