#include <unordered_map>
#include <string>
#include <stdexcept>

#include "http/methods.h"

namespace http {
    methods to_method(const std::string& str) {
        static const std::unordered_map<std::string, http::methods> conversion_map{
                { "GET", http::methods::GET },
                { "HEAD", http::methods::HEAD },
                { "POST", http::methods::POST },
                { "PUT", http::methods::PUT },
                { "DELETE", http::methods::DELETE },
                { "CONNECT", http::methods::CONNECT },
                { "OPTIONS", http::methods::OPTIONS },
                { "TRACE", http::methods::TRACE },
                { "PATCH", http::methods::PATCH }
        };

        auto conversion = conversion_map.find(str);
        if (conversion == conversion_map.end()) {
            throw std::runtime_error("Unable to convert \"" + str + "\" to http::method");
        }
        return conversion->second;
    }

}

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
