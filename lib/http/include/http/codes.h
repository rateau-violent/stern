#ifndef HTTP_CODES_H
#define HTTP_CODES_H

#include <stdexcept>

namespace http {
    enum class codes {
        // informational response
        CONTINUE = 100,
        SWITCHING_PROTOCOLS = 101,
        PROCESSING = 102,
        EARLY_HINTS = 103,
        OK = 200,
        CREATED = 201,
        ACCEPTED = 202,
        NON_AUTHORITATIVE_INFORMATION = 203,
        NO_CONTENT = 204,
        RESET_CONTENT = 205,
        PARTIAL_CONTENT = 206,
        MULTI_STATUS = 207,
        ALREADY_REPORTED = 208,
        IM_USED = 226,
        // redirections
        MULTIPLE_CHOICES = 300,
        MOVED_PERMANENTLY = 301,
        FOUND = 302,
        SEE_OTHER = 303,
        NOT_MODIFIED = 304,
        USE_PROXY = 305,
        SWITCH_PROXY = 306,
        TEMPORARY_REDIRECT = 307,
        PERMANENT_REDIRECT = 308,
        // client errors
        BAD_REQUEST = 400,
        UNAUTHORIZED = 401,
        PAYMENT_REQUIRED = 402,
        FORBIDDEN = 403,
        NOT_FOUND = 404,
        METHOD_NOT_ALLOWED = 405,
        NOT_ACCEPTABLE = 406,
        PROXY_AUTHENTICATION_REQUIRED = 407,
        REQUEST_TIMEOUT = 408,
        CONFLICT = 409,
        GONE = 410,
        LENGTH_REQUIRED = 411,
        PRECONDITION_FAILED = 412,
        PAYLOAD_TOO_LARGE = 413,
        URI_TOO_LONG = 414,
        UNSUPPORTED_MEDIA_TYPE = 415,
        RANGE_NOT_SATISFIABLE = 416,
        EXPECTATION_FAILED = 417,
        I_M_A_TEAPOT = 418,
        MISDIRECTED_REQUEST = 421,
        UNPROCESSABLE_CONTENT = 422,
        LOCKED = 423,
        FAILED_DEPENDENCY = 424,
        TOO_EARLY = 425,
        UPGRADE_REQUIRED = 426,
        PRECONDITION_REQUIRED = 428,
        TOO_MANY_REQUESTS = 429,
        REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
        UNAVAILABLE_FOR_LEGAL_REASONS = 451,
        // server errors
        INTERNAL_SERVER_ERROR = 500,
        NOT_IMPLEMENTED = 501,
        BAD_GATEWAY = 502,
        SERVICE_UNAVAILABLE = 503,
        GATEWAY_TIMEOUT = 504,
        HTTP_VERSION_NOT_SUPPORTED = 505,
        VARIANT_ALSO_NEGOTIATES = 506,
        INSUFFICIENT_STORAGE = 507,
        LOOP_DETECTED = 508,
        NOT_EXTENDED = 510,
        NETWORK_AUTHENTICATION_REQUIRED = 511
    };
}

namespace std {
    inline string to_string(http::codes code) {
        switch (code) {
            case http::codes::CONTINUE: return "CONTINUE";
            case http::codes::SWITCHING_PROTOCOLS: return "SWITCHING PROTOCOLS";
            case http::codes::PROCESSING: return "PROCESSING";
            case http::codes::EARLY_HINTS: return "EARLY HINTS";
            case http::codes::OK: return "OK";
            case http::codes::CREATED: return "CREATED";
            case http::codes::ACCEPTED: return "ACCEPTED";
            case http::codes::NON_AUTHORITATIVE_INFORMATION: return "NON AUTHORITATIVE INFORMATION";
            case http::codes::NO_CONTENT: return "NO_CONTENT";
            case http::codes::RESET_CONTENT: return "RESET_CONTENT";
            case http::codes::PARTIAL_CONTENT: return "PARTIAL_CONTENT";
            case http::codes::MULTI_STATUS: return "MULTI STATUS";
            case http::codes::ALREADY_REPORTED: return "ALREADY REPORTED";
            case http::codes::IM_USED: return "I M USED";
            case http::codes::MULTIPLE_CHOICES: return "MULTIPLE_CHOICES";
            case http::codes::MOVED_PERMANENTLY: return "MOVED PERMANENTLY";
            case http::codes::FOUND: return "FOUND";
            case http::codes::SEE_OTHER: return "SEE OTHER";
            case http::codes::NOT_MODIFIED: return "NOT MODIFIED";
            case http::codes::USE_PROXY: return "USE PROXY";
            case http::codes::SWITCH_PROXY: return "SWITCH PROXY";
            case http::codes::TEMPORARY_REDIRECT: return "TEMPORARY REDIRECT";
            case http::codes::PERMANENT_REDIRECT: return "PERMANENT REDIRECT";
            case http::codes::BAD_REQUEST: return "BAD REQUEST";
            case http::codes::UNAUTHORIZED: return "UNAUTHORIZED";
            case http::codes::PAYMENT_REQUIRED: return "PAYMENT REQUIRED";
            case http::codes::FORBIDDEN: return "FORBIDDEN";
            case http::codes::NOT_FOUND: return "NOT FOUND";
            case http::codes::METHOD_NOT_ALLOWED: return "METHOD NOT ALLOWED";
            case http::codes::NOT_ACCEPTABLE: return "NOT ACCEPTABLE";
            case http::codes::PROXY_AUTHENTICATION_REQUIRED: return "PROXY AUTHENTICATION REQUIRED";
            case http::codes::REQUEST_TIMEOUT: return "REQUEST TIMEOUT";
            case http::codes::CONFLICT: return "CONFLICT";
            case http::codes::GONE: return "GONE";
            case http::codes::LENGTH_REQUIRED: return "LENGTH REQUIRED";
            case http::codes::PRECONDITION_FAILED: return "PRECONDITION FAILED";
            case http::codes::PAYLOAD_TOO_LARGE: return "PAYLOAD TOO LARGE";
            case http::codes::URI_TOO_LONG: return "URI TOO LONG";
            case http::codes::UNSUPPORTED_MEDIA_TYPE: return "UNSUPPORTED MEDIA TYPE";
            case http::codes::RANGE_NOT_SATISFIABLE: return "RANGE_NOT SATISFIABLE";
            case http::codes::EXPECTATION_FAILED: return "EXPECTATION FAILED";
            case http::codes::I_M_A_TEAPOT: return "I M A TEAPOT";
            case http::codes::MISDIRECTED_REQUEST: return "MISDIRECTED REQUEST";
            case http::codes::UNPROCESSABLE_CONTENT: return "UNPROCESSABLE CONTENT";
            case http::codes::LOCKED: return "LOCKED";
            case http::codes::FAILED_DEPENDENCY: return "FAILED DEPENDENCY";
            case http::codes::TOO_EARLY: return "TOO EARLY";
            case http::codes::UPGRADE_REQUIRED: return "UPGRADE REQUIRED";
            case http::codes::PRECONDITION_REQUIRED: return "PRECONDITION REQUIRED";
            case http::codes::TOO_MANY_REQUESTS: return "TOO MANY REQUESTS";
            case http::codes::REQUEST_HEADER_FIELDS_TOO_LARGE: return "REQUEST HEADER FIELDS TOO LARGE";
            case http::codes::UNAVAILABLE_FOR_LEGAL_REASONS: return "UNAVAILABLE FOR LEGAL REASONS";
            case http::codes::INTERNAL_SERVER_ERROR: return "INTERNAL_SERVER_ERROR";
            case http::codes::NOT_IMPLEMENTED: return "NOT_IMPLEMENTED";
            case http::codes::BAD_GATEWAY: return "BAD_GATEWAY";
            case http::codes::SERVICE_UNAVAILABLE: return "SERVICE_UNAVAILABLE";
            case http::codes::GATEWAY_TIMEOUT: return "GATEWAY_TIMEOUT";
            case http::codes::HTTP_VERSION_NOT_SUPPORTED: return "HTTP_VERSION_NOT_SUPPORTED";
            case http::codes::VARIANT_ALSO_NEGOTIATES: return "VARIANT_ALSO_NEGOTIATES";
            case http::codes::INSUFFICIENT_STORAGE: return "INSUFFICIENT_STORAGE";
            case http::codes::LOOP_DETECTED: return "LOOP_DETECTED";
            case http::codes::NOT_EXTENDED: return "NOT_EXTENDED";
            case http::codes::NETWORK_AUTHENTICATION_REQUIRED: return "NETWORK_AUTHENTICATION_REQUIRED";
        }
        throw std::runtime_error("Unable to convert http::version to string");
    }

}

#endif /* !HTTP_CODES_H */
