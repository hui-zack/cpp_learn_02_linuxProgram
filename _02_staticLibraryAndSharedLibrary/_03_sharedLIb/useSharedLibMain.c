/*********************************
* @Author   : Hui
* @Aata     : 2022/12/18 0:21
* @Describe : 
* @Keyword  : 
*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 3-2-1-1 导入动态库的头文件 */
#include "resource/myMath.h"

int main(int argc, char *argv[]) {

    /* 3-2-1-2 使用动态库函数 */
    int result = add(10, 5);

    printf("[C] hello shared library, the result = %d\n", result);

    return 0;
}