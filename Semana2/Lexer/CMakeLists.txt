cmake_minimum_required (VERSION 2.6)
project (test1)

include_directories(${PROJECT_SOURCE_DIR})

include_executables(${PROJECT_NAME} lexer.cpp main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -std=c++14)



//cmake /direccion del archivo cmake