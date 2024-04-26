cmake_minimum_required(VERSION 3.27)
project(LRU_Cache)

set(CMAKE_CXX_STANDARD 20)

add_executable(LRU_Cache main.cpp
        LRU_Cache.h
        LRU_Cache.cpp)
