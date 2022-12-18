/*********************************
* @Author   : Hui
* @Aata     : 2022/12/18 0:21
* @Describe : 
* @Keyword  : 
*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "resource/myMath.h"

int main(int argc, char *argv[]) {

    /* 1-1-4 在main中include头文件, 调用add函数 */
    int result = add(10, 5);

    printf("[C] hello makefile, the result = %d\n", result);

    system("pause");
    return 0;
}