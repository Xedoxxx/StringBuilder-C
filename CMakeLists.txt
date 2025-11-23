cmake_minimum_required(VERSION 3.14)

project(sstrbld_t VERSION 0.0.2 LANGUAGES C)

set(CMAKE_C_STANDART 11)
set(CMAKE_C_STANDARTZ_REQUIRED ON)

add_library(strbld_t src/string_builder.c)
target_include_directories(strbld_t PUBLIC include)

enable_testing()
add_subdirectory(tests)