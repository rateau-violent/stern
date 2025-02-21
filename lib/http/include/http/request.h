#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>

#include "method.h"

namespace http {
    struct request {
        request(const std::string&) {
            path = "";
            method = http::methods::GET;
        }

        std::string path;
        methods method;
    };
}

#endif /* !HTTP_REQUEST_H */
