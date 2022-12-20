#! /bin/bash

if [ ! -d build  ];then
  mkdir build
fi

rm build/* -rf && cd build && cmake .. && make && echo -e "\n---- run code ----" && ./../bin/mainDemo