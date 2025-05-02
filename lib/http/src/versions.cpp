#include "http/versions.h"

#include <stdexcept>
#include <unordered_map>
#include <utility>

namespace http {
    enum versions to_version(const std::string& str) {
        static const std::unordered_map<std::string, enum versions> conversion_map{
            { "HTTP/0.9", versions::HTTP_0_9 },
            { "HTTP/1.0", versions::HTTP_1_0 },
            { "HTTP/1.1", versions::HTTP_1_1 },
            { "HTTP/2", versions::HTTP_2 },
            { "HTTP/3", versions::HTTP_3 }
        };

        auto conversion = conversion_map.find(str);
        if (conversion == conversion_map.end()) {
            throw std::runtime_error("Unable to convert \"" + str + "\" to http::version value");
        }
        return conversion->second;
    }
}

namespace std {
    string to_string(const enum http::versions version) {
        switch (version) {
            case http::versions::HTTP_0_9: return "HTTP/0.9";
            case http::versions::HTTP_1_0: return "HTTP/1.0";
            case http::versions::HTTP_1_1: return "HTTP/1.1";
            case http::versions::HTTP_2: return "HTTP/2";
            case http::versions::HTTP_3: return "HTTP/3";
        }

        throw std::runtime_error("Unable to convert http::version to string");
    }

}
