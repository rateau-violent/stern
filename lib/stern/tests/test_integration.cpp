#include "helper/client.h"
#include "fixture/test_fixture.h"

#include "stern/stern.h"

#include <criterion/criterion.h>

void setup() {
    test_fixture::get_instance().start_server();
}

void tear_down() {
    test_fixture::get_instance().stop_server();
}

Test(stern_integration_tests, base, .init = setup, .fini = tear_down) {

    try {
        tests::helper::client client("127.0.0.1", 3000);
        auto res = client.get("/users");

        std::cout << "___" << std::endl;
        std::cout << "response = " << (int)res.getCode() << ": " << res.getBody().to_string() << std::endl;

    } catch(const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
    }
}
