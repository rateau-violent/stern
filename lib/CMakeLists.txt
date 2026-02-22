add_subdirectory(http)
add_subdirectory(stern)
add_subdirectory(network)

if (ENABLE_TESTS)
add_subdirectory(tests)
endif ()