#ifndef STERN_TEST_CLIENT_H
#define STERN_TEST_CLIENT_H

#include <array>
#include <iostream>

#include <asio.hpp>

using asio::ip::tcp;

namespace tests::helper {
    class tcp_client {
        public:
            explicit tcp_client(const std::string& uri_base): _uri_base{uri_base} {}

            std::string send(const std::string& request) {
                asio::io_context io_context;

                tcp::resolver resolver(io_context);
                tcp::resolver::results_type endpoints = resolver.resolve(_uri_base, "daytime");

                tcp::socket socket(io_context);
                asio::connect(socket, endpoints);

                std::vector<char>req_buff(request.begin(), request.end());
                socket.send(asio::buffer(req_buff), request.size());

                std::array<char, 128> buf;
                asio::error_code error;

                size_t len = socket.read_some(asio::buffer(buf), error);

                if (error == asio::error::eof)
                    throw std::runtime_error("Connection closed"); // Connection closed cleanly by peer.
                else if (error)
                    throw asio::system_error(error); // Some other error.

                return std::string(buf.data());
            }
        private:
          std::string _uri_base;
    };
}

#endif /* STERN_TEST_CLIENT_H */

