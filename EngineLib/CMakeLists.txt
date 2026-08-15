cmake_minimum_required(VERSION 3.15)
project(EngineLib CXX)

add_library(EngineLib STATIC
        app/engine.cpp
        app/engine.h
)

# Link SDL and Glad, and include GLM and STB header paths
target_link_libraries(EngineLib PUBLIC
        SDL3::SDL3                     # Use SDL2::SDL2 if using SDL2
        glad                           # The glad OpenGL loader target
)

target_include_directories(EngineLib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../submodule/glm>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../submodule/stb>
        $<INSTALL_INTERFACE:include>
)