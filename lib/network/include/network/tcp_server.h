#ifndef NETWORK_TCP_SERVER_H
#define NETWORK_TCP_SERVER_H

#include <variant>

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
             * @brief Configuration for tcp_server
             */
            struct config {
                /// The port the server will listen on
                std::size_t port;
                /// The connection's configuration
                tcp_connection::config connection_config;
            };

            /**
            * @param [in] config The tcp server configuration
            * @param [in] packet_handler Function called when a packet is received
            */
            explicit tcp_server(const config& config, std::function<void (std::shared_ptr<tcp_connection>, const packet_descriptor&)> packet_handler);

            /**
            * @brief Starts the server
            */
            void start();
            /**
            * @brief Stops the server
            */
            void stop();

        private:
            const config _conf;
            asio::io_context _ctx;
            asio::ip::tcp::acceptor _acceptor;
            std::function<void (std::shared_ptr<tcp_connection>, const packet_descriptor&)>  _packet_handler;

            void _start_accept();
            void _handle_accept(std::shared_ptr<tcp_connection> new_connection, const std::error_code& error);
    };
}

#endif /* !NETWORK_TCP_SERVER_H */
