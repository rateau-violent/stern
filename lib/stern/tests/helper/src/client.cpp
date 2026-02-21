#include <stdexcept>
#include <sstream>

#include <curl/curl.h>

#include "helper/client.h"

namespace {

    class Curler {
        public:
            explicit Curler() {
                CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
                if(result != CURLE_OK) {
                    throw std::runtime_error{make_error_message("curl_global_init", result)};
                }

                _curl = curl_easy_init();
            }

            ~Curler() {
                if (_curl) {
                    curl_easy_cleanup(_curl);
                }
                curl_global_cleanup();
            }

            void get(const std::string& url, long& response_code, std::string& response_content) const {
                curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());

                fill_response_content(response_content);

                make_request();

                curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &response_code);
            }

            void post(const std::string& url, const http::body_type& body, long& response_code, std::string& response_content) const {
                curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());

                std::size_t content_len;
                char* raw_content = copy_request_body(body, content_len);

                /* Now specify the POST data */
                curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, raw_content);

                /* Specify headers */
                specify_headers({
                    {"Content-Length", std::to_string(body.size() + 2)},
                    {"Content-Type", body.is_json() ? "application/json" : "text/html; charset=UTF-8"}
                });

                fill_response_content(response_content);

                make_request();

                curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &response_code);
                free(raw_content);
            }

            void put(const std::string& url, const http::body_type& body, long& response_code, std::string& response_content) const {

                curl_easy_setopt(_curl, CURLOPT_CUSTOMREQUEST, "PUT");
                curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());


                std::size_t content_len;
                char* raw_content = copy_request_body(body, content_len);

                /* Now specify the PUT data */
                curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, raw_content);

                /* Specify headers */
                specify_headers({
                    {"Content-Length", std::to_string(body.size() + 2)},
                    {"Content-Type", body.is_json() ? "application/json" : "text/html; charset=UTF-8"}
                });

                fill_response_content(response_content);

                make_request();
                curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &response_code);
                free(raw_content);
            }

        private:
            CURL* _curl;

            static std::string make_error_message(const std::string& fct_name, CURLcode code) {
                std::stringstream ss;

                ss << "Curl error: " << fct_name << "() failed:" << curl_easy_strerror(code) << ".";
                return ss.str();
            }

            static std::size_t get_response_content(void *contents, std::size_t size, std::size_t nmemb, std::string *s) {
                std::size_t newLength = size * nmemb;

                s->append(static_cast<char*>(contents), newLength);
                return newLength;
            }

            static char* copy_request_body(const http::body_type& body, std::size_t& body_len) {
                body_len = body.size();
                char* body_str = static_cast<char*>(malloc(body_len + 1));
                std::memcpy(body_str, body.to_string().c_str(), body_len);
                return body_str;
            }

            void specify_headers(const std::unordered_map<std::string, std::string>& headers) const {
                curl_slist* hs = nullptr;

                for (const auto& [header, value]: headers) {
                    hs = curl_slist_append(hs, std::string(header + ": " + value).c_str());
                }
                curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, hs);
            }

            void fill_response_content(std::string& response_content) const {
                curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, get_response_content);
                curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &response_content);
            }

            void make_request() const {
                /* Perform the request, result gets the return code */
                auto result = curl_easy_perform(_curl);
                /* Check for errors */
                if(result != CURLE_OK) {
                    throw std::runtime_error{make_error_message("curl_easy_perform", result)};
                }
            }
    };

}

namespace tests::helper {
    client::client(const std::string& ip, std::size_t port): _ip{ip}, _port{port} {
    }

    http::response client::get(const std::string& path) const {
        long response_code;
        std::string response_content;
        auto url = compute_url(path);
        Curler curl;

        curl.get(url, response_code, response_content);

        return http::response(static_cast<http::codes>(response_code), response_content);
    }

    http::response client::post(const std::string& path, const http::body_type& body) const {
        long response_code;
        std::string response_content;
        Curler curl;
        std::string url = compute_url(path);

        curl.post(url, body, response_code, response_content);
        return http::response{static_cast<http::codes>(response_code), response_content};
    }

    http::response client::put(const std::string& path, const http::body_type& body) const {
        long response_code;
        std::string response_content;
        Curler curl;
        std::string url = compute_url(path);

        curl.put(url, body, response_code, response_content);
        return http::response{static_cast<http::codes>(response_code), response_content};
    }

    std::string client::compute_url(const std::string& path) const {
        return "http://" + _ip + ":" + std::to_string(_port) + "/" + path;
    }

}
