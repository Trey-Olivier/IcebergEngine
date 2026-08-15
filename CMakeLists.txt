cmake_minimum_required(VERSION 3.15)
project(PizzaSrcWorkspace CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your OpenGL submodules
add_subdirectory(submodule/SDL)
add_subdirectory(submodule/glad)
# Note: glm and stb are typically header-only and don't need add_subdirectory,
# you just include their directories inside your engine library.

# Add your sub-projects
add_subdirectory(EngineLib)
add_subdirectory(Game)