add_library(backend STATIC
    include/backend/backend.h
    include/backend/controller_base.h
    include/backend/concepts.h
    include/backend/module_base.h
    include/backend/parameters.h
    include/backend/server.h
)

target_link_libraries(backend
    http
    network
    reflectcpp
)

target_include_directories(backend PUBLIC
    include
    ../http/include # TODO
)

set_target_properties(backend PROPERTIES LINKER_LANGUAGE CXX)