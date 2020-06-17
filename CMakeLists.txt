cmake_minimum_required(VERSION 3.16)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_executable(test main.cpp sort/heap.cpp sort/bucket.cpp greedy/section.cpp greedy/greedy.cpp double_pointer/double_pointer.cpp binary_search/binary_search.cpp divide_and_conquer/divide_and_conquer.cpp search/bfs.cpp search/module.cpp search/dfs.cpp search/backtracking.cpp basic/string_operation.cpp basic/sort.cpp basic/basic_math.cpp basic/pointer.cpp math/math_problem.cpp math/math_method.cpp basic/basic_sort.cpp linked_list/lined_list_problem.cpp)