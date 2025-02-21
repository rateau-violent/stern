#include <iostream>

#include <asio/placeholders.hpp>

#include "network/tcp_server.h"

#include <asio/read_until.hpp>
#include <asio/streambuf.hpp>


namespace network {
    tcp_server::tcp_server(std::size_t port, std::function<void (std::shared_ptr<tcp_connection>, const std::string&)>  request_handler):
        _port{port},
        _ctx{},
        _acceptor{_ctx, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), _port)},
        _request_handler{std::move(request_handler)} {
    }

    void tcp_server::start() {
        try {
            _start_accept();
            _ctx.run();
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void tcp_server::stop() {
        _ctx.stop();
    }

    void tcp_server::_start_accept() {
        std::shared_ptr<tcp_connection> new_connection = tcp_connection::create(_ctx);

        _acceptor.async_accept(new_connection->socket(),
            std::bind(&tcp_server::_handle_accept, this, new_connection, asio::placeholders::error));
    }


    void tcp_server::_handle_accept(std::shared_ptr<tcp_connection> new_connection, const std::error_code& error_code) {
        if (!error_code) {
            new_connection->listen([new_connection, this](const std::string& data) {
                _request_handler(new_connection, data);
            });
        }
        _start_accept();
    }
}
