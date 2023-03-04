cmake_minimum_required(VERSION 3.12)

project(brainfuck_compiler VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(
  GLOB sources
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(bfc ${sources})
add_compile_options(-O3)

target_include_directories(bfc PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

install(TARGETS bfc DESTINATION bin)
