#include "http_server.hpp"

#include <thread>

auto makeTaskString(const std::string &method, const Request &req) -> std::string;

HttpServer::HttpServer(MessageQueue<Request> &queue) : request_queue(queue) {
    std::cout << "Server online" << std::endl;
}

auto HttpServer::requestHandler() -> void {
    // TODO: multi-threads support with native implementation
    auto req = request_queue.pop();
    std::string passwd;
    std::cout << "Enter password: ";
    std::cin >> passwd;
    std::string taskString = "sshpass -p " + passwd + " " + makeTaskString("scp", req);
    std::cout << taskString << std::endl;
    FILE *pipe = popen(taskString.c_str(), "r");
    if (pipe == nullptr) {
        // handle error
        std::cerr << "error" << std::endl;
    } else {
        std::cout << "success" << std::endl;
    }
    // Close the pipe when done
    pclose(pipe);
    requestHandler();
}

auto HttpServer::start() -> void {
    requestHandler();
}

auto makeTaskString(const std::string &method, const Request &req) -> std::string {
    return method + " " + req.orig_path + " " + req.dest_path;
}