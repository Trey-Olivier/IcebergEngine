cmake_minimum_required(VERSION 3.20)

# 1. Force CMake to use our local vcpkg BEFORE defining the project
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# 2. Now define the project
project(MyEngine3D CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(EngineLib)
add_subdirectory(Game)