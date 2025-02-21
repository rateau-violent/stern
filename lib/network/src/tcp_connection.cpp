#include <iostream>

#include <asio/read_until.hpp>
#include <asio/write.hpp>
#include <asio/placeholders.hpp>

#include "network/tcp_connection.h"

namespace network {
    std::shared_ptr<tcp_connection> tcp_connection::create(asio::io_context& io_context) {
        return std::shared_ptr<tcp_connection>(new tcp_connection(io_context));
    }

    asio::ip::tcp::socket& tcp_connection::socket() {
        return _socket;
    }

    void tcp_connection::listen(std::function<void (const std::string&)> request_handler) {
        asio::async_read_until(_socket, _request, "\r\n\r\n",  std::bind(&tcp_connection::_handle_request, shared_from_this(),
            asio::placeholders::error, asio::placeholders::bytes_transferred, std::move(request_handler)));
    }

    tcp_connection::tcp_connection(asio::io_context& io_context):
        _socket(io_context) {
    }

    void tcp_connection::send(const std::string& str) {
        asio::streambuf response;
        std::ostream res_stream(&response);

        res_stream << str;

        asio::async_write(_socket, response, std::bind(&tcp_connection::_after_response, shared_from_this(),
            asio::placeholders::error, asio::placeholders::bytes_transferred));
    }

    void tcp_connection::_handle_request(const std::error_code& error_code, std::size_t bytes_read, std::function<void (const std::string&)> request_handler) {
        std::string data{std::istreambuf_iterator<char>(&_request),std::istreambuf_iterator<char>()};

        request_handler(data);
    }

    void tcp_connection::_after_response(const std::error_code& error_code, std::size_t bytes_sent) {
        _socket.close();
    }

}