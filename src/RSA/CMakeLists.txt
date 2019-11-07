cmake_minimum_required(VERSION 3.0.0)

project(RSA)

add_library(rsa_math STATIC math.cpp)

add_executable(rsa "")
target_sources(rsa
    PRIVATE
        application.cpp
        main.cpp
)
target_link_libraries(rsa rsa_math ntl)
