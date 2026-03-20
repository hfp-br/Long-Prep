cmake_minimum_required(VERSION 3.16)
project(Test_Atributos)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

add_executable(Test_Atributos
    Long-Prep/src/item.cpp
    Long-Prep/src/player.cpp
    Long-Prep/src/Test.cpp
)
