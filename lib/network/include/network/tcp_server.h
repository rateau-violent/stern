#ifndef NETWORK_TCP_SERVER_H
#define NETWORK_TCP_SERVER_H

#include <any>

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>

#include "network/tcp_connection.h"

namespace network {
    /**
    * @brief TCP server class
    */
    class tcp_server {
        public:
            /**
            * @param port [in] The port the server will run on
            */
            explicit tcp_server(std::size_t port, std::function<void (std::shared_ptr<tcp_connection>, const std::string&)>  request_handler);

            /**
            * @brief Starts the server
            */
            void start();
            /**
            * @brief Stops the server
            */
            void stop();

        private:
            std::size_t _port;
            asio::io_context _ctx;
            asio::ip::tcp::acceptor _acceptor;
            std::function<void (std::shared_ptr<tcp_connection>, const std::string&)>  _request_handler;

            void _start_accept();
            void _handle_accept(std::shared_ptr<tcp_connection> new_connection, const std::error_code& error);
    };
}

#endif /* !NETWORK_TCP_SERVER_H */
