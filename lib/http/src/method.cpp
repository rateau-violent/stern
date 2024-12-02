#include <unordered_map>
#include <string>

#include "http/method.h"

namespace std {
    string to_string(http::methods m) {
        static std::unordered_map<http::methods, string> converter{
            { http::methods::GET, "GET" },
            { http::methods::HEAD, "HEAD" },
            { http::methods::POST, "POST" },
            { http::methods::PUT, "PUT" },
            { http::methods::DELETE, "DELETE" },
            { http::methods::CONNECT, "CONNECT" },
            { http::methods::OPTIONS, "OPTIONS" },
            { http::methods::TRACE, "TRACE" },
            { http::methods::PATCH, "PATCH" }
        };

        return converter[m];
    }
}
