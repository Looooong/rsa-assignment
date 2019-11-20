cmake_minimum_required(VERSION 3.0.0)

project(RSA)

add_library(rsa_key STATIC private_key.cpp public_key.cpp)
add_library(rsa_math STATIC math.cpp math/prime.cpp)
add_library(rsa_utils STATIC utils.cpp)

add_executable(rsa "")
target_sources(rsa
    PRIVATE
        application.cpp
        main.cpp
)
target_link_libraries(rsa rsa_key rsa_math rsa_utils ntl)
