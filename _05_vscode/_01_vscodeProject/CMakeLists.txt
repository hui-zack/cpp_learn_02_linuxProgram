# cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 14)
project(_01_useCmak VERSION 1.0 LANGUAGES CXX)




message("this is a string")
message(${project_version})
# set(CMAKE_BUILD_TYPE "Debug" )#调试模式

add_executable(test01 helloCmake.cpp)#测试代码