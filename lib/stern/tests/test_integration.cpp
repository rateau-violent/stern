#include "helper/client.h"
#include "helper/test_fixture.h"

#include "stern/stern.h"

#include <criterion/criterion.h>


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
