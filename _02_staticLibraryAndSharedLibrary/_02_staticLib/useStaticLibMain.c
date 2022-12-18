/*********************************
* @Author   : Hui
* @Aata     : 2022/12/17 23:51
* @Describe : 
* @Keyword  : 
*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* 2-2-1-1 导入静态库的头文件 */
#include "resource/myMath.h"

int main(int argc, char *argv[]) {

    /* 2-2-1-2 使用静态库函数 */
    int result = sub(10, 5);
    printf("[C] hello static library, the result = %d\n", result);

    system("pause");
    return 0;
}