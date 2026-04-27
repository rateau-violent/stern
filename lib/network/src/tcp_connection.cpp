#include <iostream>

#include <asio/read_until.hpp>
#include <asio/write.hpp>
#include <asio/placeholders.hpp>

#include "network/tcp_connection.h"

namespace network {
    std::shared_ptr<tcp_connection> tcp_connection::create(const config& conf,
        asio::io_context& io_context) {
        return std::shared_ptr<tcp_connection>(new tcp_connection(conf, io_context));
    }

    asio::ip::tcp::socket& tcp_connection::socket() {
        return _socket;
    }

    void tcp_connection::listen(std::function<void (const packet_descriptor&)> packet_handler) {
        _receive_strategy(std::move(packet_handler));
    }

    tcp_connection::tcp_connection(const config& conf, asio::io_context& io_context):
        _socket(io_context),
        _receive_strategy(_get_receive_strategy(conf)) {
    }

    void tcp_connection::send(const packet_descriptor& packet) {
        asio::streambuf response;
        std::ostream res_stream(&response);

        res_stream << packet.data;

        asio::async_write(_socket, response, std::bind(&tcp_connection::_after_response, shared_from_this(),
            asio::placeholders::error, asio::placeholders::bytes_transferred));
    }

    tcp_connection::strategy tcp_connection::_get_receive_strategy(const config& conf) {
       if (conf.strategy_type == config::read_strategy::READ_UNTIL) {
          return [&conf, this](std::function<void (const packet_descriptor&)> packet_handler) {
              asio::async_read_until(_socket, _request, std::get<std::string>(conf.stop_condition),
                  [packet_handler, this](const std::error_code& error_code, std::size_t bytes_read) {
                  _handle_request(error_code, bytes_read, packet_handler);
              });
          };
       }
       throw std::runtime_error("network::tcp_connection: Unknown read_strategy type.");
    }

    void tcp_connection::_handle_request(const std::error_code& error_code, std::size_t bytes_read, std::function<void (const packet_descriptor&)> request_handler) {
        std::vector<std::uint8_t> packet{std::istreambuf_iterator<char>(&_request),std::istreambuf_iterator<char>()};

        request_handler({packet.data(), packet.size()});
    }

    void tcp_connection::_after_response(const std::error_code& error_code, std::size_t bytes_sent) {
        _socket.close();
    }

}