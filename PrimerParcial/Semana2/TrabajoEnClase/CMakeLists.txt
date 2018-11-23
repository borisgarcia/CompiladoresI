cmake_minimum_required (VERSION 2.6)
project (Lexer)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} Lexer.cpp main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)
