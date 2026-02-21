#ifndef STERN_TEST_CLIENT_H
#define STERN_TEST_CLIENT_H

#include <http/response.h>

namespace tests::helper {
    class client {
        public:

            /**
             *  Creates a client object
             *  @param [in] ip the server's ip
             *  @param [in] port the server's port
             */
            explicit client(const std::string& ip, std::size_t port);

            [[nodiscard]] http::response get(const std::string& path) const;
            [[nodiscard]] http::response post(const std::string& path, const http::body_type& body) const;

        private:
            std::string _ip;
            std::size_t _port;

            std::string compute_url(const std::string& path) const;

    };
}

#endif /* STERN_TEST_CLIENT_H */

