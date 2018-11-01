cmake_minimum_required (VERSION 2.6)
project (Sintactico)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} Sintax.cpp Lexer.cpp main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)
