#ifndef NETWORK_TCP_CONNECTION
#define NETWORK_TCP_CONNECTION

#include <memory>

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/streambuf.hpp>

namespace network {
    /**
    * @brief Represents a tcp client connection
    */
    class tcp_connection: public std::enable_shared_from_this<tcp_connection> {
        public:
            /**
            * @brief Creates and returns a new tcp_connection as a std::shared_ptr
            */
            static std::shared_ptr<tcp_connection> create(asio::io_context& io_context);

            /**
            * @brief Retrieves the connection's socket
            */
            asio::ip::tcp::socket& socket();

            /**
            * @brief Listens on the connection
            */
            void listen(std::function<void (const std::string&)> request_handler);

            void send(const std::string& response);

        private:
            asio::ip::tcp::socket _socket;
            asio::streambuf _request;

            explicit tcp_connection(asio::io_context& io_context);

            void _handle_request(const std::error_code& error_code, std::size_t bytes_read, std::function<void (const std::string&)> request_handler);

            void _after_response(const std::error_code& error_code, std::size_t bytes_sent);

    };
}


#endif /* !NETWORK_TCP_CONNECTION */
