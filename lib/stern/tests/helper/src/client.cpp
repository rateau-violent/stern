#include <stdexcept>
#include <sstream>

#include <curl/curl.h>

#include "helper/client.h"

namespace {
    size_t get_response_content(void *contents, std::size_t size, std::size_t nmemb, std::string *s) {
        std::size_t newLength = size * nmemb;

        s->append(static_cast<char*>(contents), newLength);
        return newLength;
    }

    std::string make_curl_error(const std::string& fct_name, CURLcode code) {
        std::stringstream ss;

        ss << "Curl error: " << fct_name << "() failed:" << curl_easy_strerror(code) << ".";
        return ss.str();
    }
}

namespace tests::helper {
    client::client(const std::string& ip, std::size_t port): _ip{ip}, _port{port} {
    }

    http::response client::get(const std::string& path) const {
        CURL *curl;
        long response_code;
        std::string response_content;

        CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
        if(result != CURLE_OK) {
            throw std::runtime_error{make_curl_error("curl_global_init", result)};
        }

        curl = curl_easy_init();
        if(curl) {
            const std::string url = compute_url(path);
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_response_content);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_content);

            /* Perform the request, result gets the return code */
            result = curl_easy_perform(curl);
            /* Check for errors */
            if(result != CURLE_OK) {
                throw std::runtime_error{make_curl_error("curl_easy_perform", result)};
            }

            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

            /* always cleanup */
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
        return http::response(static_cast<http::codes>(response_code), response_content);
    }

    http::response client::post(const std::string& path, const http::body_type& body) const {
        CURL *curl;
        long response_code;
        std::string response_content;

        CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
        if(result != CURLE_OK){
            throw std::runtime_error{make_curl_error("curl_global_init", result)};
        }

        /* get a curl handle */
        curl = curl_easy_init();
        if(curl) {
            std::string url = compute_url(path);

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            auto body_len = body.size();
            char* body_str = static_cast<char*>(malloc(body_len + 1));
            std::memcpy(body_str, body.to_string().c_str(), body_len);
            /* Now specify the POST data */
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body_str);

            /* Specify headers */
            curl_slist *hs = nullptr;
            hs = curl_slist_append(hs, std::string("Content-Length: " + std::to_string(body.size() + 2)).c_str());
            if (body.is_json()) {
                hs = curl_slist_append(hs, "Content-Type: application/json");
            } else {
                hs = curl_slist_append(hs, "Content-Type: text/html; charset=UTF-8");
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_response_content);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_content);

            /* Perform the request, result gets the return code */
            result = curl_easy_perform(curl);
            /* Check for errors */
            if(result != CURLE_OK) {
                throw std::runtime_error{make_curl_error("curl_easy_perform", result)};
            }

            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

            /* always cleanup */
            curl_easy_cleanup(curl);
            free(body_str);
        }
        curl_global_cleanup();
        return http::response{static_cast<http::codes>(response_code), response_content};
    }

    std::string client::compute_url(const std::string& path) const {
        return "http://" + _ip + ":" + std::to_string(_port) + "/" + path;
    }

}
