[toc]   
    [GDB调试器简介](#GDB调试器简介)  
    [Gdb调试流程](#Gdb调试流程)  

## GDB调试器简介
    * gdb是gcc的调试工具
    * gdb四个主要功能:
        启动程序, 按照自定义的要求随心所欲的运行程序
        可让程序在断电处停止(断电可以是条件表达式)
        当程序被挺住时, 可以检查此时程序中发生的事情
        可以动态的改变程序的执行环境

    * 使用gdb调试程序, 必须加上-g参数, 否则将无法看到程序的函数名, 变量名, 只能看到一堆内存地址

    
## Gdb调试流程
-   [1-1 gcc编译目标文件(.o文件)时添加-g参数](./_01_useGdb/makefile)
    > gcc编译所有的的目标文件(.o文件)时, 都要加-g参数, 才能被gdb正确调试

-   [1-2 使用gdb调试程序]
```shell
    # 执行目录:  _04_gdb/_01_useGdb
     
    gdb useMakefileMain       # 格式: gdb [可执行文件名]  //windows下一般是exe文件
    
    # gdb shell中常用命令
        # 设置和显示外部参数
        set args 10 hui       # 设置程序的外部输入参数(如果有的话)
        show args             # 显示设置的外部参数'
        
        # 程序执行常用命令
        run                   # 执行到第一个断点     
        c                     # continue的简写, 执行到下一个断点
        start                 # 执行到代码的第一行
        
        # list查看命令, list可简写为l
        list 8                # 以指定行数为中心显示代码(显示10行)
        list main             # 显示main函数并显示代码
        list add.c:add        # 切换到add.c:add位置并显示代码
        list -                # 切换到当前文件开头
        list add.c: 1         # 切换到add.c文件第一行显示代码
        
        set listsize count    # 设置显示源代码的行数为count
      
        # break设置断点, break可以简写为b
        # 设置和删除断点
        b 10                  # 在当前文件的第10行设置断店
        b add.c: add          # 在add.c文件的add函数位置设置断点
        b sub.c: 6            # 在sub文件的第6行设置断点
        d 4                   # 删除id为4的断点
    
        # 断电查看和断点开关
        i b                   # 显示所有的断点(info break的缩写)
        disable 4             # 将id为4的断点设置为无效
        disable 1-4           # 将id从1到4的断点设置为无效
        enable 4              # 将id为4的断点设置为有效
        enable 1-4            # 将id从1到4的断点设置为有效
        next                  # 往下执行一步
        
        # 显示变量的值
        p result              # 打印变量result的值
        d result              # 设置result变量值自动显示(d是display的缩写)
        undisplay             # 关闭result变量值自动显示
        info display          # 显示所有自动显示变量值的变量 
        
        # 查看变量的类型
        ptype result          # 打印result变量的类型
        
```