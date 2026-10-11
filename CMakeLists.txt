cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)

# Create executable
add_executable(snake src/main.c src/game.c src/renderer.c)

# Link SDL2
target_link_libraries(snake ${SDL2_LIBRARIES})
target_include_directories(snake PRIVATE ${SDL2_INCLUDE_DIRS})

# Compiler flags
if(MSVC)
    target_compile_options(snake PRIVATE /W4)
else()
    target_compile_options(snake PRIVATE -Wall -Wextra -Wpedantic)
endif()
