cmake_minimum_required(VERSION 3.20)
project(EngineLib CXX)

# 1. Find all packages (vcpkg ensures these are downloaded and built)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(entt CONFIG REQUIRED)
find_package(joltphysics CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Stb REQUIRED)

# 2. Define your engine library
add_library(EngineLib STATIC
        src/application.cpp
        src/renderer.cpp
)

# 3. Include directories for your own engine headers
target_include_directories(EngineLib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 4. Link everything uniformly
target_link_libraries(EngineLib PUBLIC
        glfw
        glad::glad
        glm::glm
        assimp::assimp
        EnTT::entt
        JoltPhysics::JoltPhysics
        imgui::imgui
        Stb::Stb
)