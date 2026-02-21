#ifndef STERN_TEST_CLIENT_H
#define STERN_TEST_CLIENT_H

#include <http/response.h>

namespace tests::helper {
    class client {
        public:

            explicit client(const std::string& ip, std::size_t port, const std::string& logfile = "/dev/null");

            [[nodiscard]] http::response get(const std::string& path) const;

        private:
            std::string _ip;
            std::size_t _port;
            std::string _logfile;

            static std::size_t get_response_content(void *contents, std::size_t size, std::size_t nmemb, std::string *s);
    };
}

#endif /* STERN_TEST_CLIENT_H */

