#include "http/error.h"

namespace http::error {
    error::error(codes c, const std::string& m): code{c}, message{m} {}

    bad_request::bad_request(const std::string& message):
        error(codes::BAD_REQUEST, message) {}

    unauthorized::unauthorized(const std::string& message):
        error(codes::UNAUTHORIZED, message) {}

    payment_required::payment_required(const std::string& message):
        error(codes::PAYMENT_REQUIRED, message) {}

    forbidden::forbidden(const std::string& message):
        error(codes::FORBIDDEN, message) {}

    not_found::not_found(const std::string& message):
        error(codes::NOT_FOUND, message) {}

    method_not_allowed::method_not_allowed(const std::string& message):
        error(codes::METHOD_NOT_ALLOWED, message) {}

    not_acceptable::not_acceptable(const std::string& message):
        error(codes::NOT_ACCEPTABLE, message) {}

    proxy_authentication_required::proxy_authentication_required(const std::string& message):
        error(codes::PROXY_AUTHENTICATION_REQUIRED, message) {}

    request_timeout::request_timeout(const std::string& message):
        error(codes::REQUEST_TIMEOUT, message) {}

    conflict::conflict(const std::string& message):
        error(codes::CONFLICT, message) {}

    gone::gone(const std::string& message):
        error(codes::GONE, message) {}

    length_required::length_required(const std::string& message):
        error(codes::LENGTH_REQUIRED, message) {}

    precondition_failed::precondition_failed(const std::string& message):
        error(codes::PRECONDITION_FAILED, message) {}

    payload_too_large::payload_too_large(const std::string& message):
        error(codes::PAYLOAD_TOO_LARGE, message) {}

    uri_too_long::uri_too_long(const std::string& message):
        error(codes::URI_TOO_LONG, message) {}

    unsupported_media_type::unsupported_media_type(const std::string& message):
        error(codes::UNSUPPORTED_MEDIA_TYPE, message) {}

    range_not_satisfiable::range_not_satisfiable(const std::string& message):
        error(codes::RANGE_NOT_SATISFIABLE, message) {}

    expectation_failed::expectation_failed(const std::string& message):
        error(codes::EXPECTATION_FAILED, message) {}

    i_m_a_teapot::i_m_a_teapot(const std::string& message):
        error(codes::I_M_A_TEAPOT, message) {}

    misdirected_request::misdirected_request(const std::string& message):
        error(codes::MISDIRECTED_REQUEST, message) {}

    unprocessable_content::unprocessable_content(const std::string& message):
        error(codes::UNPROCESSABLE_CONTENT, message) {}

    locked::locked(const std::string& message):
        error(codes::LOCKED, message) {}

    failed_dependency::failed_dependency(const std::string& message):
        error(codes::FAILED_DEPENDENCY, message) {}

    too_early::too_early(const std::string& message):
        error(codes::TOO_EARLY, message) {}

    upgrade_required::upgrade_required(const std::string& message):
        error(codes::UPGRADE_REQUIRED, message) {}

    precondition_required::precondition_required(const std::string& message):
        error(codes::PRECONDITION_REQUIRED, message) {}

    too_many_requests::too_many_requests(const std::string& message):
        error(codes::TOO_MANY_REQUESTS, message) {}

    request_header_fields_too_large::request_header_fields_too_large(const std::string& message):
        error(codes::REQUEST_HEADER_FIELDS_TOO_LARGE, message) {}

    unavailable_for_legal_reasons::unavailable_for_legal_reasons(const std::string& message):
        error(codes::UNAVAILABLE_FOR_LEGAL_REASONS, message) {}

    internal_server_error::internal_server_error(const std::string& message):
        error(codes::INTERNAL_SERVER_ERROR, message) {}

    not_implemented::not_implemented(const std::string& message):
        error(codes::NOT_IMPLEMENTED, message) {}

    bad_gateway::bad_gateway(const std::string& message):
        error(codes::BAD_GATEWAY, message) {}

    service_unavailable::service_unavailable(const std::string& message):
        error(codes::SERVICE_UNAVAILABLE, message) {}

    gateway_timeout::gateway_timeout(const std::string& message):
        error(codes::GATEWAY_TIMEOUT, message) {}

    http_version_not_supported::http_version_not_supported(const std::string& message):
        error(codes::HTTP_VERSION_NOT_SUPPORTED, message) {}

    variant_also_negotiates::variant_also_negotiates(const std::string& message):
        error(codes::VARIANT_ALSO_NEGOTIATES, message) {}

    insufficient_storage::insufficient_storage(const std::string& message):
        error(codes::INSUFFICIENT_STORAGE, message) {}

    loop_detected::loop_detected(const std::string& message):
        error(codes::LOOP_DETECTED, message) {}

    network_authentication_required::network_authentication_required(const std::string& message):
        error(codes::NETWORK_AUTHENTICATION_REQUIRED, message) {}

}
