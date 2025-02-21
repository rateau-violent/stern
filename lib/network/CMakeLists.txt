add_library(network STATIC
    src/tcp_server.cpp
    src/tcp_connection.cpp
)

find_package(asio REQUIRED)

target_link_libraries(network
        asio::asio
)

target_include_directories(network PUBLIC
        include
)

set_target_properties(network PROPERTIES LINKER_LANGUAGE CXX)