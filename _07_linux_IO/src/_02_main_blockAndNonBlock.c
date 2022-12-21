#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void forCharString(int argc, char* charArr[]){
    printf("input argv = ");
    for(int i = 0; i < argc; i++){
        printf(" %s", charArr[i]);
    }
    printf("\n");

    /* 2-1 同时读取普通文件, 判断是否为阻塞调用 */
}

void printCharArray(char charArrp[]){
    for(int i=0; i< strlen(charArrp); i++){
        printf("[%d]", charArrp[i]);
    }
    printf("\n");
}

int openFile(char* filePath){
    int fp = open(filePath, O_RDWR);
    if (fp == -1){
        perror("open failed");
        return -1;
    }
    return fp;
}

int main(int argc, char* argv[]){
    // forCharString(argc, argv);
    int fp = openFile("../linux_IO知识点.md");
  
    // int fp = openFile("../resource/test.txt");
    char buf[1024];
    sizeof(buf);
    memset(buf, 0x00, sizeof(buf));             //重置空间所有位置为null
    int fileLength = lseek(fp, 0, SEEK_SET);
    int result = read(fp, buf, sizeof(buf));
    if (result == -1){
        perror("read failed");
    }
    printf("%s", buf);

   
    return 0;
}