cmake_minimum_required(VERSION 3.0.0)

project(RSA)

add_executable(rsa "")
target_sources(rsa
    PRIVATE
        application.cpp
        main.cpp
        math.cpp
)
target_link_libraries(rsa ntl)
