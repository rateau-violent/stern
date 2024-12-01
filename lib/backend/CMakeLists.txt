add_library(backend STATIC
    include/backend/controller_base.h
)

target_link_libraries(backend
    http
)

target_include_directories(backend PUBLIC
    include
    ../http/include # TODO
)

set_target_properties(backend PROPERTIES LINKER_LANGUAGE CXX)