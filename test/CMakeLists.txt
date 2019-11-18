cmake_minimum_required(VERSION 3.0.0)

project(RSA_tests)

add_subdirectory(lib/Catch2)

include_directories(lib/Catch2/single_include)
include_directories(../src)

add_executable(rsa_tests "")
target_sources(rsa_tests
    PRIVATE
        key.cpp
        main.cpp
        math.cpp
        math/prime.cpp
)
target_link_libraries(rsa_tests rsa_key rsa_math ntl Catch2::Catch2)
