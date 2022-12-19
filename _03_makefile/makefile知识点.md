[toc]  
    [Makefile的概念和学习目标](#Makefile的概念和学习目标)  
    [编写makefile文件](#编写makefile文件)  
    [Makefile变量](#Makefile变量)  
    [Makefile函数](#Makefile函数)  

## Makefile的概念和学习目标
**makefile和make**

    * 学习目标
        1. 熟练掌握规则编写简单的makefile文件
        2. 熟练使用makefile中的变量
        3. 熟练使用makefile中的函数

    * makefile文件和make命令
        makefile是一个文件, 用来管理项目工程, 其内部描述了项目中哪些些代码需要先编译, 哪些需要后编译, 哪些些需要编译成库等
        make是一个命令工具, 用来解释和执行makefile文件中的操作
    
**makefile文件的命名规范** 
    
    文件名为: makefile(没有后缀)

## 编写makefile文件
**使用makefile编译代码**
-   [1-1 编写代码]  
        [1-1-1 编写add函数](./_01_useMakefile/resource/add.c)  
        [1-1-2 编写sub函数](./_01_useMakefile/resource/sub.c)  
        [1-1-3 编写myMath.h头文件, 声明add和sub函数](./_01_useMakefile/resource/myMath.h)  
        [1-1-4 在main中include头文件, 调用add函数](./_01_useMakefile/useMakefileMain.c)  

    
-   [1-2 编写makefile]
        [方式1 一步编译为可执行文件](./_01_useMakefile/case1.makefile)
        [方式2 分步编译出可执行文件.o文件放到对应代码文件的同级目录](./_01_useMakefile/case2.makefile)
        [方式3 分步编译出可执行文件, .o文件存放在指定目录](./_01_useMakefile/case3.makefile)  
        [方式4 方式4 分步编译出可执行文件, 使用变量简化编译命令](./_01_useMakefile/case4.makefile)
    

    >  注意:
    >   上面的编译方式每一种都可以make出可执行程序, 区别仅在于编译方式的不同, 请选择最好用的一种来编译代码
    >   示例文件(makefile.*)的数字后缀和方式的排序数字相同, 如果要使用第一种方式编译, 复制makefile.1内容到makefile, 不要修改示例内容
    
---
    * makefile文件编译检查规则:
        要生成目标文件, 先去检查依赖是否都存在
            依赖都存在: 比较目标文件生成时间和依赖文件修改时间, 如果依赖有最新修改, 则重新生成目标文件
            依赖不存在: 往下找是否有依赖生成规则, 有则编译依赖文件, 没有则报错  
   


-   [1-3 在makefile目录使用make命令编译]  
```shell
    # 使用make命令根据makefile编译程序
      make

```

    方式1
        可执行文件名称: 依赖文件路径列表(空格隔开)
        (tab) gcc编译命令

## Makefile变量

-   [makefile普通变量]
        [2-1-1 定义普通变量](./_01_useMakefile/var.makefile)  
        [2-1-2 使用普通变量](./_01_useMakefile/var.makefile)  
-   [makefile系统变量]
        [2-2-1 指定系统类型的变量 CC](./_01_useMakefile/var.makefile)  
        [2-2-2 指定头文件目录的系统变量(设置gcc的-I) CPPFLAGS](./_01_useMakefile/var.makefile)  
        [2-2-3 指定编译方式的系统变量(选择设置gcc的-c, -S, -E, -WAll -g) CFLAGS](./_01_useMakefile/var.makefile)  
        [2-2-4 指定库文件的系统变量(设置gcc的-L, -l) LDFLAGS](./_01_useMakefile/var.makefile)  
    [makefile自动变量(只能用在命令中)]
        [2-3-1 表示规则中的目标 $@](./_01_useMakefile/var.makefile)  
        [2-3-3 表示所有规则的列表, 以空格分割(自动删除重复项) $^](./_01_useMakefile/var.makefile)  
        [2-3-2 表示规则列表的第一个条件 $<](./_01_useMakefile/var.makefile)  
    
---
    * makefile变量的作用
        在makefile的变量常会用于内容替换, 使用变量可以使得makefile文件易于维护, 修改起来更加简单
    * makefile变量的类型: 
        · 普通变量
        . 自带变量
        . 自动变量
    * 自动变量和规则: 
        规则指的依赖行, 如 main : add.o sub.o
            规则目标		$@ = main
            规则列表		$^ = add.o sub.o, add.o就是
            第一个条件	$< = add.o

## Makefile函数
```makefile
    # 获取当前目录下所有c文件, 并返回list
    src = ${wildcard *.c}   
    
    # 把src中的所有c文件的.c后缀修改为.o, 返回list
    objs = ${patsubst %.c, %.o, ${src}} 
    
    # 打印变量值
    result = ${warning ${srcDir}}

    # 只保留文件名(参数不能为list)
    filename = $(notdir com/fda.c)

```
