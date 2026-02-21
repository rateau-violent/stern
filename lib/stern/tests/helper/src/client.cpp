#include <stdexcept>
#include <sstream>

#include <curl/curl.h>

#include "helper/client.h"

namespace tests::helper {

    client::client(const std::string& ip, std::size_t port, const std::string& logfile):
                _ip{ip}, _port{port}, _logfile{logfile} {
    }

    http::response client::get(const std::string& path) const {
        CURL *curl;
        long response_code;
        std::string response_content;

        CURLcode result = curl_global_init(CURL_GLOBAL_ALL);
        if(result != CURLE_OK) {
            std::stringstream ss;
            ss << "Curl error: curl_global_init() failed:" << curl_easy_strerror(result) << ".";
            throw std::runtime_error{ss.str()};
        }

        curl = curl_easy_init();
        if(curl) {
            const std::string url = "http://" + _ip + ":" + std::to_string(_port) + "/" + path;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_response_content);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_content);

            /* Perform the request, result gets the return code */
            result = curl_easy_perform(curl);
            /* Check for errors */
            if(result != CURLE_OK) {
                std::stringstream ss;
                ss << "Curl error: " << "curl_easy_perform() failed:" << curl_easy_strerror(result);
                throw std::runtime_error{ss.str()};
            }

            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

            /* always cleanup */
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
        return http::response(static_cast<http::codes>(response_code), response_content);
    }

    size_t client::get_response_content(void *contents, std::size_t size, std::size_t nmemb, std::string *s) {
        std::size_t newLength = size * nmemb;

        s->append(static_cast<char*>(contents), newLength);
        return newLength;
    }

}
