cmake_minimum_required(VERSION 3.0.0)

project(RSA_tests)

add_subdirectory(lib/Catch2)

include_directories(lib/Catch2/single_include)
include_directories(../src)

add_executable(rsa_tests "")
target_sources(rsa_tests
    PRIVATE
        main.cpp
)
target_link_libraries(rsa_tests ntl Catch2::Catch2)
