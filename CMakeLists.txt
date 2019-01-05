cmake_minimum_required(VERSION 3.13)
project(numbers C)

set(CMAKE_C_STANDARD 11)

add_executable(numbers main.c my_math.c number.h number.c op.h op.c)