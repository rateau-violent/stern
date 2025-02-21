#ifndef HTTP_METHOD_H
#define HTTP_METHOD_H

namespace http {
    enum class methods {
        GET,
        HEAD,
        POST,
        PUT,
        DELETE,
        CONNECT,
        OPTIONS,
        TRACE,
        PATCH
    };

    methods to_method(const std::string&);
}

namespace std {
    string to_string(http::methods);
}

#endif /* !HTTP_METHOD_H */
