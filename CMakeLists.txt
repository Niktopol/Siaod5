cmake_minimum_required(VERSION 3.20)

project(Siaod5)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -Wpedantic -fsanitize=address -g")
add_executable(Siaod5 main.cpp bin_tree.cpp b_tree.cpp hash_table.cpp structures.cpp binf_worker.cpp)