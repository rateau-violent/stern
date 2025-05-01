#ifndef HTTP_ERROR_H
#define HTTP_ERROR_H

#include <string>

#include "codes.h"

namespace http::error {

    struct error {
        explicit error(codes code, const std::string& message);

        codes code;
        std::string message;
    };

    struct bad_request: public error {
      explicit bad_request(const std::string& message = "Bad Request");
    };

    struct unauthorized: public error {
        explicit unauthorized(const std::string& message = "Unauthorized");
    };

    struct payment_required: public error {
        explicit payment_required(const std::string& message = "Payment Required");
    };

    struct forbidden: public error {
        explicit forbidden(const std::string& message = "Forbidden");
    };

    struct not_found: public error {
        explicit not_found(const std::string& message = "Not Found");
    };

    struct method_not_allowed: public error {
        explicit method_not_allowed(const std::string& message = "Method Not Allowed");
    };

    struct not_acceptable: public error {
        explicit not_acceptable(const std::string& message = "Not Acceptable");
    };

    struct proxy_authentication_required: public error {
        explicit proxy_authentication_required(const std::string& message = "Proxy Authentication Required");
    };

    struct request_timeout: public error {
        explicit request_timeout(const std::string& message = "Request Timeout");
    };

    struct conflict: public error {
        explicit conflict(const std::string& message = "Conflict");
    };

    struct gone: public error {
        explicit gone(const std::string& message = "Gone");
    };

    struct length_required: public error {
        explicit length_required(const std::string& message = "Length Required");
    };

    struct precondition_failed: public error {
        explicit precondition_failed(const std::string& message = "Precondition Failed");
    };

    struct payload_too_large: public error {
        explicit payload_too_large(const std::string& message = "Payload Too Large");
    };

    struct uri_too_long: public error {
        explicit uri_too_long(const std::string& message = "Uri Too Long");
    };

    struct unsupported_media_type: public error {
        explicit unsupported_media_type(const std::string& message = "Unsupported Media Type");
    };

    struct range_not_satisfiable: public error {
        explicit range_not_satisfiable(const std::string& message = "Range Not Satisfiable");
    };

    struct expectation_failed: public error {
        explicit expectation_failed(const std::string& message = "Expectation Failed");
    };

    struct i_m_a_teapot: public error {
        explicit i_m_a_teapot(const std::string& message = "I'm A Teapot");
    };

    struct misdirected_request: public error {
        explicit misdirected_request(const std::string& message = "Misdirected Request");
    };

	struct unprocessable_content: public error {
		explicit unprocessable_content(const std::string& message = "Unprocessable Content");
	};

    struct locked: public error {
        explicit locked(const std::string& message = "Locked");
    };

    struct failed_dependency: public error {
        explicit failed_dependency(const std::string& message = "Failed Dependency");
    };

	struct too_early: public error {
        explicit too_early(const std::string& message = "Too Early");
    };

    struct upgrade_required: public error {
        explicit upgrade_required(const std::string& message = "Upgrade Required");
    };

    struct precondition_required: public error {
        explicit precondition_required(const std::string& message = "Precondition Required");
    };

    struct too_many_requests: public error {
        explicit too_many_requests(const std::string& message = "Too Many Requests");
    };

    struct request_header_fields_too_large: public error {
        explicit request_header_fields_too_large(const std::string& message = "Request Header Fields Too Large");
    };

    struct unavailable_for_legal_reasons: public error {
        explicit unavailable_for_legal_reasons(const std::string& message = "Unavailable For Legal Reasons");
    };

    struct internal_server_error: public error {
        explicit internal_server_error(const std::string& message = "Internal Server Error");
    };

    struct not_implemented: public error {
        explicit not_implemented(const std::string& message = "Not Implemented");
    };

    struct bad_gateway: public error {
        explicit bad_gateway(const std::string& message = "Bad Gateway");
    };

    struct service_unavailable: public error {
        explicit service_unavailable(const std::string& message = "Service Unavailable");
    };

    struct gateway_timeout: public error {
        explicit gateway_timeout(const std::string& message = "Gateway Timeout");
    };

    struct http_version_not_supported: public error {
        explicit http_version_not_supported(const std::string& message = "HTTP Version Not Supported");
    };

    struct variant_also_negotiates: public error {
        explicit variant_also_negotiates(const std::string& message = "Variant Also Negotiates");
    };

    struct insufficient_storage: public error {
        explicit insufficient_storage(const std::string& message = "Insufficient Storage");
    };

    struct loop_detected: public error {
        explicit loop_detected(const std::string& message = "Loop Detected");
    };

    struct not_extended: public error {
        explicit not_extended(const std::string& message = "Not Extended");
    };

    struct network_authentication_required: public error {
        explicit network_authentication_required(const std::string& message = "Network Authentication Required");
    };
}

#endif /* !HTTP_ERROR_H */