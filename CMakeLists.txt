cmake_minimum_required (VERSION 2.6)
project (tinyjson_test C)

# Set C language standard to C99
set(CMAKE_C_STANDARD 99)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(tinyjson src/tiny_json.c)
add_executable(tinyjson_test src/test.c)
target_link_libraries(tinyjson_test tinyjson)