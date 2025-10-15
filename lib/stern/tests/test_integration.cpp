#include <main_module.h>

#include "helper/client.h"

#include "stern/stern.h"

#include <criterion/criterion.h>


// #include "helper/test_fixture.h"



class test_fixture {
    using server_type = stern::server<example::http_framework>;
    public:

        static test_fixture& get_instance() {
            static test_fixture helper;

            return helper;
        }

        void start_server() {
            server_thread = std::jthread([]() {
                get_server().start();
            });
            // mandatory sleep to let the server start properly
            sleep(2);
        }

        void stop_server() {
            sleep(1);
            get_server().stop();
            server_thread.request_stop();
        }
        static server_type& get_server() {
            static server_type server{3000, example::main_module()};

            return server;
        }
    private:
        explicit test_fixture() = default;

        std::jthread server_thread;
};

void setup() {
    test_fixture::get_instance().start_server();
}

void tear_down() {
    test_fixture::get_instance().stop_server();
}

Test(stern_integration_tests, base, .init = setup, .fini = tear_down) {
    tests::helper::tcp_client client("localhost:3000");

    auto res = client.send("GET / HTTP/1.1\r\n"
        "Host: localhost:3000\r\n"
        "\r\n");
}
