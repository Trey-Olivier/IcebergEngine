cmake_minimum_required(VERSION 3.15)
project(Game CXX)

add_executable(Game WIN32
        main.cpp
)

target_link_libraries(Game PUBLIC
        EngineLib
)