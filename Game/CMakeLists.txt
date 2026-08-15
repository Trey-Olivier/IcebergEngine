cmake_minimum_required(VERSION 3.15)
project(Game CXX)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

if(WIN32 AND NOT MINGW)
    message(WARNING "This project's Windows build has only been verified with MinGW.")
endif()

add_executable(Game WIN32
        main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../EngineLib/src/entrypoint.cpp
)

target_link_libraries(Game PRIVATE
        EngineLib
        SDL3::SDL3
)

add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3-shared>
        $<TARGET_FILE_DIR:Game>
        COMMENT "Copying SDL3.dll next to Game.exe"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

