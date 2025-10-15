#ifndef STERN_TEST_FIXTURE_H
#define STERN_TEST_FIXTURE_H

#include "stern/stern.h"

#include "utils/http_framework.h"

class test_fixture {
    public:
        using server_type = stern::server<example::http_framework>;

        static test_fixture& get_instance();

        void start_server();

        void stop_server();

        static server_type& get_server();

    private:
        std::jthread server_thread;

        explicit test_fixture() = default;
};

#endif
