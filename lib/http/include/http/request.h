#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <unordered_map>

#include "methods.h"
#include "versions.h"

namespace http {
    struct request {
        request(const std::string&);

        http::versions version;
        std::string path;
        methods method;
        std::unordered_map<std::string, std::string> headers;
    };
}

#endif /* !HTTP_REQUEST_H */
