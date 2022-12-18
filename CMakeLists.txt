cmake_minimum_required(VERSION 3.17)
project(cpp_learn_02_linuxProgram)

set(CMAKE_CXX_STANDARD 14)



add_executable(useMakefileMain _03_makefile/_01_useMakefile/useMakefileMain.c _03_makefile/_01_useMakefile/resource/add.c _03_makefile/_01_useMakefile/resource/sub.c)