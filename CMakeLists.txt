cmake_minimum_required(VERSION 3.25)
project(treap)

set(CMAKE_CXX_STANDARD 17)

add_executable(treap main.cpp)

include_directories(src)
add_subdirectory(src)
target_link_libraries(treap del_lib)

add_subdirectory(tests)
