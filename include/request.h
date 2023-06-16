#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>

struct Request {
    enum method { // (R)equest (M)ethod + <method name>
        RMstatus,
        RMnew,
        RMkill,
        RMenable,
        RMdisable,
        RMexit
    } request_method;
    enum type { // (R)equest (T)ype + <type name>
        RTsync,
        RTpush,
        RTpull
    } request_type;
    std::string orig_path;
    std::string dest_path;
//    int freq;

    Request(method _method, type _type, std::string &o_path, std::string &d_path) :
            request_method(_method), request_type(_type), orig_path(o_path), dest_path(d_path) {
    }

    friend auto operator<<(std::ostream &os, Request const &request) -> std::ostream & {
        os << "method: " << request.request_method
           << " type: " << request.request_type
           << " orig_path: " << request.orig_path
           << " dest_path: " << request.dest_path;
        return os;
    }
};

#endif