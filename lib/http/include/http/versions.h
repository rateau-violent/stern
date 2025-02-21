#ifndef HTTP_VERSION_H
#define HTTP_VERSION_H

#include <string>

namespace http {
    enum class versions {
        HTTP_0_9,
        HTTP_1_0,
        HTTP_1_1,
        HTTP_2,
        HTTP_3
    };

    versions to_version(const std::string&);
}

namespace std {
    string to_string(http::versions);
}

#endif /* !HTTP_VERSION_H */
