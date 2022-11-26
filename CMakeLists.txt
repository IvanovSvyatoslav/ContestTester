cmake_minimum_required(VERSION 3.23)
project(TestingFramework
        VERSION 1.0
        DESCRIPTION "A small C++ testing framework for online contests"
        LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)

add_executable(TestingFramework main.cpp)
