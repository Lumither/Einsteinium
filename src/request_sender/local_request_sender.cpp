#include "request_sender.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include <vector>

#include "request.h"

#include "magic_enum/magic_enum.hpp"
#include "boost/pfr/core.hpp"

auto getPrefix(const int& index) -> std::string;

static int inputCnt = 0;

auto LocalRequestSender::stdinRead() -> void {
    if (inputCnt == 1) {
        return;
    }
    std::cout << ":: ";
    getline(std::cin, input_string);
    inputParse();
}

auto LocalRequestSender::inputParse() -> void {
    if (input_string == "exit") {
        exit(0);
    }
    // parse input
    std::stringstream ss{input_string};
    std::string token_s;
    int token_cnt = 0;
    // std::vector<std::string> input_s;
    Request::method tmp_method;
    Request::type tmp_type;
    std::string tmp_orig_path;
    std::string tmp_dest_path;

    while (ss >> token_s) {
        switch (token_cnt) {
        case 0:
            if (auto token_parsed = magic_enum::enum_cast<Request::method>(getPrefix(token_cnt) + token_s);
                token_parsed.has_value()) {
                tmp_method = token_parsed.value();
            } else {
                std::cerr << "[E] invalid input!" << std::endl;
                std::cerr.flush();
            }
            token_cnt++;
            break;
        case 1:
            if (auto token_parsed = magic_enum::enum_cast<Request::type>(getPrefix(token_cnt) + token_s);
                token_parsed.has_value()) {
                tmp_type = token_parsed.value();
            } else {
                std::cerr << "[E] invalid input!" << std::endl;
                std::cerr.flush();
            }
            token_cnt++;
            break;
        case 2:
            tmp_orig_path = token_s;
            token_cnt++;
            break;
            case 3:
            tmp_dest_path = token_s;
            request_queue.push(Request(tmp_method, tmp_type, tmp_orig_path, tmp_dest_path));
            token_cnt++;
            inputCnt++;
            break;
        default:
            token_cnt = 0;
            break;
        }
    }


    stdinRead();
}

auto LocalRequestSender::start() -> void {
    stdinRead();
}

LocalRequestSender::LocalRequestSender(MessageQueue<Request>& queue) : request_queue(queue) {
    std::cout << "local request sender online" << std::endl;
}

auto getPrefix(const int& index) -> std::string {
    switch (index) {
    case 0:
        return "RM";
    case 1:
        return "RT";
    default:
        return "";
    }
}