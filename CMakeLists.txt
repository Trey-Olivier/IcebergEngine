cmake_minimum_required(VERSION 3.15)
project(PizzaSrcWorkspace CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(EngineLib)
add_subdirectory(Game)