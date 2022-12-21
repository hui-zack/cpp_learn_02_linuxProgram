## linux_IO的基本概念和名词
    * 文件内容从内存写入硬盘的三种情况
        1 调用了flush
        2 缓存区已满自动写入
        3 正常关闭文件时自动写入

    * 读和写时都会引起指针的移动

    * windows下使用fopen函数打开一个文件时, 返回一个FILE * fp, 该指针指向了一个结构体(该结构体有三个重要的成员变量)
        · 文件描述符 
            通过文件描述符可以找到文件的inode, 通过inode可以中岛对应的数据块
        · 文件指针
            都和写都使用这个指针, 都会引起文件指针的bianhua
        · 文件缓存区
            读和写的内容都会进入文件缓存区(内存), 主要目的是为了减少对硬盘的读写次数, 提高硬盘效率

    * 库函数和系统函数的关系
        库函数是对系统函数的进一步封装

    * 用户区和内核区
        每一个运行的程序, 操作系统都会为其分配一个0~4G的虚拟地址空间
            * 0-3G为用户区
                环境变量
                命令行参数
                共享库
                占空间                      (较小)
                堆空间                      (较大)
                .bss(未初始化的全局变量)
                .data(已初始化的全局变量)
                收保护的地址                (代码段, 二进制机器指令)

            * 3-4G为内核区(内核空间收保护, 不能对该区域进行读写)
                内存管理
                进程管理                    (重要内容PCB-进程控制块-是一个结构体)
                设备驱动管理
                vfs虚拟文件系统 

    * PCB/进程控制块
        内核区区域重要的部分-进程管理, 进程管理中有一个区域就是PCB(本质是一个结构体),PCB中有文件描述符表,
        文件描述符表中存放着打开的文件描述符, 涉及到IO的操作都会用改这个文件描述符 

    * 文件描述符表
        每一个刚打开的文件, 都会自动的去创建文件描述符(无论文件是否被同时打开, 一个文件都只对应一个描述符), 并默认具有三个属性, 加入到进程管理的文件描述符表
            1. STDIN_FILENO   ->  标准输入
            2. STDOUT_FILENO  ->  标准输出
            3. STDERR_FILENO  ->  标准错误

        文件描述符表默认具有1024个位置, 如果文件只打开不关闭的话, 一但1024个位置都被占用, 就无法再打开该文件了

        > 备注:
            pcb: task_strut, 该结构体位置: /usr/src/linux_hearders-4.4.0-97/include/linux/sched.h: 1390

    * 内核中IO操作的代码流程
        虚拟地址空间 -> 内核区 -> PCB -> 文件描述表 -> 文件描述符 -> 文件IO操作使用文件描述符 

## linux常用头文件
```C
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>          
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
```

## 文件操作
**IO常用函数**  

--- 
-   代码  
    [1-1 使用open打开文件](./src/_01_mainBasicIO.c)  
    [1-2 使用write写入char*字符串](./src/_01_mainBasicIO.c)  
    [1-3 使用lseek移动文件指针到开头](./src/_01_mainBasicIO.c)  
    [1-4 使用read函数读取内容](./src/_01_mainBasicIO.c)  
    [1-5 使用close关闭文件](./src/_01_mainBasicIO.c)  
    [1-6 使用lseek获取文件大小](./src/_01_mainBasicIO.c)  
---
-   open函数
    ```C
        int open(const char* pathName, int flags);
        int open(const char* pathName, int flags, mode_t mode);
    ```
    
    ```C
            功能: 用于打开文件
            参数:
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
                
            返回值:
                非-1    // 打开成功, 返回最小且未被占用的文件描述符
                -1      // 打开失败, 返回-1, 并设置errno
    ```
-   write函数
    ```C
        ssize_t write(int fd, const void* buf,  size_t count)
    ```
   
    ```C
            功能:
                向打开的设备或文件中写入数据
            参数:
                fd          // 文件表述符
                buf         // 写入硬盘的数据将先被缓冲到泛形指针buf中, 
                count       // 设定缓存区存放的最大字节数
            返回值:
                >-1         // 读取到的总字节数
                -1          // 出错, 并设置errno
    ```
-   lessk函数:
    ```C
        off_t lseek(int fd, off_t offset, int whence);
    ```
    
    ```C
            功能: 使用该函数来移动文件指针
            函数参数:
                fd                                                      // 文件表述符
                offset                                                  // 参数offset的函数取决与whence
                    whence为SEEK_SET(文件开头位置)   文件偏移量将设置为offset             // 移动到文件开头
                    whence为SEEK_CUR(文件当前位置)   文件偏移量被设置为cfo + offset       // offset可为正, 也可为负
                    whence为SEEK_END(文件结尾位置)   文件偏移量为文件长度 + offset        // offset可为正, 也可为负  
                count                                                   // 设定缓存区存放的最大字节数
            说明: 
                1. 所有打开的文件都会有一个当前文件偏移量, 以下简称cfo, cfo通常是一个非负整数
                2. 文件被打开时, cfo会被初始化为0, 除非使用了O_APPEND
                3. cfo的单位为字节, 增量为读写的字节数

    ```

-   read函数    
    ```C
        ssize_t read(int fd, void* buf, size_t count);
    ```

    ```C
        功能:
            从打开的文件/设备中获取数据
        参数: 
            fd      // 文件表述符
            buf     // 读取的数据将被缓冲到泛形指针buf中
            count   // 设定缓存区存放的最大字节数
        返回值:
            >0      // 读取到的总字节数
            =0      // 文件读取完毕
            -1      // 出错, 并设置errno
    ```

-   close函数
    ```C
        int close(int fd);
    ```

    ```C
            功能: 用于关闭已打开的文件
            参数: 
                fd: 文件描述符
            返回值: 
                0       // 关闭成功
                -1      // 关闭失败, 并设置errno

            说明:
                1. 但一个进程结束时, 内核将对该进程所有未被关闭的文件描述符调用close关闭
                2. 对于一个成年累月运行的程序(比如网络服务器), 代开的文件描述符一定要记得close, 否则随着打开的文件越来越多, 将占用大量的文件描述符和系统资源
    ```

## perror和errno

-   简要说明
    ```
    每个进程中都会有全局变量errno和全局函数perror, 当出错时, 错误信息会存储到errno中, 可以使用perror函数将其打印出来
    ```
-   实例
    ```C
    char* filePath = "../resource/test.txt";
    int fp = open(filePath, O_RDWR | O_CREAT, 0777);

    if (fp == -1){
        perror("open error")
    }
    ```

## 阻塞和非阻塞
-   阻塞的概念
    ```
    阻塞调用    ->    指调用结果返回之前，当前线程会被挂起。调用线程只有在得到结果之后才会返回。
    非阻塞调用  ->    指在不能立刻得到结果之前，该调用不会阻塞当前线程。
    ```