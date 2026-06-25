cmake_minimum_required(VERSION 3.10)
project(Lox
    VERSION 0.1.0
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/main.cpp
    src/lox.cpp
    src/scanner.cpp
)

# Create executable
add_executable(lox ${SOURCES})

# Include directories
target_include_directories(
    lox
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Compiler flags
target_compile_options(lox PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wshadow
)