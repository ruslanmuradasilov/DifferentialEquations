cmake_minimum_required(VERSION 3.12)
project(differenial_equations_task1)

set(CMAKE_CXX_STANDARD 14)

add_executable(differenial_equations_task1 main_32.c func_32.c odu_32.c odu_32.h in.txt out.txt plot.c)