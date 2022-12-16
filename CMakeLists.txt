cmake_minimum_required(VERSION 3.17)
project(cpp_learn_02_linuxProgram)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_learn_02_linuxProgram
        _02_makefile/_01_staticLib/useStaticLib.cpp _02_makefile/_01_staticLib/resource/add.cpp _02_makefile/_01_staticLib/resource/sub.cpp)
