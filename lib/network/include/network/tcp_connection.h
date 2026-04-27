#ifndef NETWORK_TCP_CONNECTION
#define NETWORK_TCP_CONNECTION

#include <memory>
#include <variant>
#include <string>

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/streambuf.hpp>

#include "packet_descriptor.h"

namespace network {
    /**
    * @brief Represents a tcp client connection
    */
    class tcp_connection: public std::enable_shared_from_this<tcp_connection> {
    public:

        /**
         * @brief Configuration for tcp_connection class
         */
        struct config {
            /**
             * Implemented receive strategies
             */
            enum class read_strategy {
                READ_UNTIL
            };

            /// Strategy type used to receive packets
            read_strategy strategy_type;
            /// Stop condition for receiving packets
            std::variant<std::string> stop_condition;
        };

        /**
        * @brief Creates and returns a new tcp_connection as a std::shared_ptr
        */
        static std::shared_ptr<tcp_connection> create(const config& conf, asio::io_context& io_context);

        /**
        * @brief Retrieves the connection's socket
        */
        asio::ip::tcp::socket& socket();

        /**
        * @brief Listens on the connection
        */
        void listen(std::function<void (const packet_descriptor&)> packet_handler);

        void send(const packet_descriptor& response);

    private:
        using strategy = std::function<void (std::function<void (const packet_descriptor&)>)>;

        asio::ip::tcp::socket _socket;
        asio::streambuf _request;
        strategy _receive_strategy;

        explicit tcp_connection(const config& conf, asio::io_context& io_context);

        [[nodiscard]] strategy _get_receive_strategy(const config& conf);

        void _handle_request(const std::error_code& error_code, std::size_t bytes_read, std::function<void (const packet_descriptor&)> request_handler);

        void _after_response(const std::error_code& error_code, std::size_t bytes_sent);

    };
}


#endif /* !NETWORK_TCP_CONNECTION */
