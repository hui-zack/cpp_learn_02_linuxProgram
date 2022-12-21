#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    
    /* 1-1 使用open打开文件 */
    char* filePath = "../resource/test.txt";
    int fp = open(filePath, O_RDWR | O_CREAT, 0777);
        /* 参数:
                pathName            // 文件的路径, 可以是全路径或则相对路径
                flags               // 打开方式, 只能指定一个
                    必选项:
                        O_RDPNLY    // 只读打开
                        O_WRONLY    // 只写打开
                        O_RDWR      // 可读可写打开
                    可选项:
                        O_APPEND    // 表示追加, 如果文件中已有内容, 将会写入到文件末尾
                        O_CREAT     // 打开时如果文件不存在就创建该文件
                        O_EXCL      // 在指定了O_CREAT模式时, 如果文件存在则出错返回
                        O_TRUNC     // 如果文件已存在, 将长度截断为0字节
                        O_NONBLOCK  // 主要用于设备文件, 以O_NONBLOCK打开可以做到非阻塞I/O
                mode:               // 表示文件的访问权限
                    0777            // 设置文件权限, 16进制要补个0
         */
    
    fp == -1 ? perror("open error\n") : printf("open file =  %s\n", filePath); 

    /* 1-2 使用write写入char*字符串 */
    char* text = "this is a test code"; 
    int writeFlag = write(fp, text, strlen(text));
    
    writeFlag == -1 ? perror("write error\n") : printf("write text to %s\n", filePath); 


    /* 1-3 使用lseek移动文件指针到开头 */
    lseek(fp, 0, SEEK_SET);        
    
    /* 1-4 使用read函数读取内容 */
    char buf[1024];
    memset(buf, 0x00, sizeof(buf));
    int readSize = read(fp, buf, sizeof(buf));
    readSize == -1 ? perror("read error\n") : printf("read from %s :\n%s\n", filePath, buf);
    
    /* 1-5 关闭文件 */
    close(fp);

    int fp2 = open(filePath, O_RDWR, 0777);
    int fileLength = lseek(fp2, 0, SEEK_END);
    printf("get lenth of %s = %d\n", filePath, fileLength);

    return 0;

}