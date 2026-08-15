cmake_minimum_required(VERSION 3.15)
project(Game CXX)

add_executable(Game
        main.cpp
)

target_link_libraries(Game PRIVATE
        EngineLib
)