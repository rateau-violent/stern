#ifndef HTTP_FRAMEXORK_H
#define HTTP_FRAMEXORK_H

#include "method.h"
#include "request.h"
#include "response.h"

namespace http {
    struct framework {
        using method_type = http::methods;
        using response_type = http::response;
        using request_type = http::request;
    };
}

#endif /* !HTTP_FRAMEXORK_H */
