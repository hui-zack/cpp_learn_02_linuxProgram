#! /bin/bash

if [ ! -d build  ];then
  mkdir build
fi

rm build/* -rf && cd build && cmake .. && make
echo -e "\n---- run code ----"  
# ../bin/_01_mainBasicIO
../bin/_02_main_blockAndNonBlock /home/hui/workspace/git_space/cpp_learn_02_linuxProgram/_07_linux_IO/resource/test.txt