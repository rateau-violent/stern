#include "test_fixture.h"

#include "stern/stern.h"

#include "utils/utils.h"

#include <main_module.h>


test_fixture& test_fixture::get_instance() {
    static test_fixture helper;

    return helper;
}

void test_fixture::start_server() {
    server_thread = std::jthread([]() {
        get_server().start();
    });
    // mandatory sleep to let the server start properly
    sleep(1);
}

void test_fixture::stop_server() {
    sleep(1);
    get_server().stop();
    server_thread.request_stop();
}

test_fixture::server_type& test_fixture::get_server() {
    static server_type server{3000, example::main_module()};

    return server;
}
