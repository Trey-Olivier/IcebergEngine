cmake_minimum_required(VERSION 3.15)
project(EngineLib CXX)

# Link SDL and Glad, and include GLM and STB header paths
add_library(glad_gl_core_46 STATIC
        vendor/glad/src/gl.c
)
target_include_directories(glad_gl_core_46 PUBLIC
        vendor/glad/include
)

add_library(EngineLib STATIC
        include/application.h
        src/application.cpp
        src/entrypoint.cpp
)

target_link_libraries(EngineLib PUBLIC
        SDL3::SDL3
        glad_gl_core_46
)

target_include_directories(EngineLib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../submodule/glm>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../submodule/stb>
        $<INSTALL_INTERFACE:include>
)