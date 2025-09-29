#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <unordered_map>

#include "body.h"
#include "methods.h"
#include "versions.h"

namespace http {
    struct request {
        explicit request(const std::string&);

        http::versions version;
        std::string path;
        methods method;
        std::unordered_map<std::string, std::string> headers;
        body_type body;
        std::unordered_map<std::string, std::string> query;
    };

    std::ostream& operator<<(std::ostream& os, const request& r);
}

#endif /* !HTTP_REQUEST_H */
