add_library(backend STATIC
    include/backend/backend.h
    include/backend/controller_base.h
    include/backend/concepts.h
    include/backend/module_base.h
    include/backend/server.h
)

find_package(asio REQUIRED)

target_link_libraries(backend
    http
    asio::asio
)

target_include_directories(backend PUBLIC
    include
    ../http/include # TODO
)

set_target_properties(backend PROPERTIES LINKER_LANGUAGE CXX)