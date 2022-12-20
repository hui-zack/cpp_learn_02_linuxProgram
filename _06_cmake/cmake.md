## cmake介绍
    * cmake是什么?
        - camke是一门跨平台的编译工具, 简化了编译步骤, camke通过用户自定义的CMakeLists.txt文件来自动生成makefile, 让开发者不必自己去写makefile, 加大的减轻了项目中编译程序的复杂性.
        - cmake使用了makefile的技术, 是建立在makefile之上的.

## linux下cmake和开发环境搭建
```shell
    # 更新apt
    sudo apt update
    
    # 一键安装gcc, g++, gdb
    sudo apt install build-essential gdb
    
    # 安装cmake
    sudo apt install cmake
    
    # 查看软件是否安装成功
    gcc -v
    g++ -v
    gdb -v
    cmake -version

```
## linux创建cmake工程

-   项目路径下新建CMakeLists.txt写入项目信息

    ```cmake
        # cmake_minimum_required(VERSION 3.17)
        project(_01_useCmake)
        
        # set(CMAKE_CXX_STANDARD 14)
    
        # set(CMAKE_BUILD_TYPE "Debug" )#调试模式
        
        add_executable(test01 helloCmake.cpp)#测试代码
    ```

-   创建cmake编译目录并构建cmake工程

    ```shell
        # 在vscode项目路径下执行
        mkdir build
        cd build
        # 根据CMmakeLists创建工程
        # windows下首次创建需要指定编译器, 之后只需使用命令 cmake [CMakeLists路径] , linux直接cmake [CMakeLists路径]
            cmake -G "MinGW Makefiles" ..  # windows
            cmake ..                       # linux 
        # 编译程序
        make 
    ```

## Cmake语法要求和概念名词:
    * cmake的语法要求:
        - cmake命令不区分大小写, 但是参数和变量名称区分大小写
        - 参数之间使用空格或则分号隔开
        - 使用${varName}来引用变量
        - 书写字符串时, 引号可以加也可以不加, 但是有空格必须加字符串(推荐字符串)

    * cmake中的概念名词
        - 目标文件(target): 
            目标文件一般指的是可执行文件和库文件:
                add_executable  ->  可执行文件常用命令
                add_library    ->  库文件常用命令
        - 命令(cmake-command):
            cmake定义的一套供开发者使用的命令
        - 变量(cmake-variable):
            变量分为两种, 第一种是cmake定义的内置变量, 另一种是开发者自己定义的变量:
                cmake的内置变量一般都以CMAKE_开头
        - 属性(cmake-properties):
            cmake为每一个项目中的文件/文件夹都定义了几个属性, 便于检索和判断

## 常用函数
```cmake
# 函数 递归获取所有子目录, 返回所有以fileEnd结尾的文件的父目录列表
MACRO(FUNC_GETDIRS result dirPath fileEnd)
  file(GLOB_RECURSE children  ${dirPath} ${dirPath}/*${fileEnd})
  SET(dirlist "") 
  list(SORT children)
  FOREACH(child ${children})
    string(REGEX REPLACE "(.*)/.*" "\\1" dirSrc ${child})
    IF(IS_DIRECTORY ${dirSrc} AND NOT "${dirSrc}" STREQUAL "${TMP}")
        message("|| Add dir = " ${dirSrc})
        LIST(APPEND dirlist ${dirSrc})
        SET(TMP  ${dirSrc})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

# 函数 递归获取所有子目录, 返回所有以fileEnd结尾的文件列表
MACRO(FUNC_GETFILES result dirPath fileEnd)
  file(GLOB_RECURSE children  ${dirPath} ${dirPath}/*${fileEnd})
  LIST(APPEND dirlist ${filesrc})
  FOREACH(child ${children})
    LIST(APPEND dirlist ${child})
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()
```


## CmakeLists基本编写规则(不包含库操作)
**cmake命令**
-   cmake基本命令
    ```cmake
        # 指定cmake的版本
        cmake_minimum_required(VERSION 3.22)    

        # 设置c++标准
        set(CMAKE_CXX_STANDARD 14)              # 使用c++14

        # 设置项目名, 项目
        project(learnCmake)                     # 设置项目名称为learnCmake
        project(learnCmake C CXX)               # 设置项目名称learnCmake, 语言为C C++ 
        project(learnCmake VERSION 1.00 CXX)    # 指定项目名称, 项目版本, 项目语言

        # 打印函数
        message("this is a string")
        # 如果在project中定义了版本号, 则版本号将被保存在变量project_version中
        message(${project_version})             # 打印项目版本号
        

        message("project dir = " ${CMAKE_BINARY_DIR})                   # 获取cmake编译目录绝对路径

        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)  # 设置静态库文件输出目录(代码中所有生成的静态库都会到这里)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)  # 设置动态库文件输出目录(代码中所有生成的动态库都会到这里)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)  # 设置可执行文件输出目录(代码中所有生成的可执行文件都会到这里)


        # 编译可执行文件 
        add_add_executable(mainDemo helloCmake.cpp)     # 为helloCmake.cpp 生成makefiles


    ```
-   cmake变量
    ```cmake
        # 设置配置文档
        # 项目路径下创建config.h.in并写入以下内容

        configure_file(config.h.in config.h)   

        # 定义普通变量
        set(myVar 1)                    # 设置普通变量

        # 定义开关变量(布尔变量)
        option(isCXX)                           # 设置布尔变量isCXX, 默认为on(true)           
        option(isC "use code is C?" off)        # 设置布尔变量isC, 编写帮助文档, value为off(false)
    ```

-   cmake流程控制语句
    ```cmake
        # debug开关
        option(DEBUG_TYPE "set debug" ON)       ## 修改该值, 需要使用cmake重新编译代码

        if(DEBUG_TYPE)
            message("debug type = true")
            set(CMAKE_BUILD_TYPE "Debug")
            
        else()
            message("debug type = false")
            
        endif()
    ```

## 通过cmake设置项目配置文件
cmake会将主CMakeLists目录下的config.h.in的内容定位为宏, 存储在config.h中, 代码内只要声明这个头文件就可以获得配置的值
-   第一步 主CMakeLists.txt的同级目录中创建config.h.in配置文件
```c++
    // 在config.h.in中使用编写项目版本()
    #define PROJECT_VERSION_MAJOR @PROJECT_VERSION_MAJOR@
    #define PROJECT_VERSION_MINOR @PROJECT_VERSION_MINOR@

```
-   第二步 在主CMakeLists.txt中配置, 使用configure_file函数将配置文件转换为config.h头文件
```cmake
    # 设置项目名称, 并指定项目住版本号1, 副版本好0, 执行语言c++
    project(myProject VERSION 1.0 LANGUAGES CXX)

    # 将config.h.in的内容加载到cmake
    configure_file(config.h.in config.h)
```
-   第三步


[在代码中使用配置文件](src/helloCmake.cpp)需要声明config.h(注意将config.h的目录添加到头文件目录中)

## 指定头文件搜索目录
-   方式1 为单个目标指定头文件路径(推荐)
```cmake=
    # 编译可执行目标
    add_executable(mainDemo src/helloCmake.cpp)     # 设置名称为mainDemo(目标)
    
    # 为mainDemo目标设置头文件搜索目录
    target_include_directories(mainDemo         # 为mainDemo目标设置头文件目录
        PUBLIC                                  # 这些目录下的头文件既能供自己使用, 也可用作外部接口
            ${PROJECT_BINARY_DIR} 
            ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}  
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}     
        PRIVATE                                 # 这些目录下的头文件只能供自己使用
        INTERFACE                               # 这些目录下的头文件只能用作外部接口
    ) 

```
-   方式2 为所有目标指定头文件路径, 多个搜索目录用空格隔开(不推荐, 搜索时间长)
```cmake
    include_directories(${PROJECT_BINARY_DIR})
```
## cmake库的生成和使用
**构建静态库/动态库**
-   第一步 在项目路径下的CMakeLists.txt中设置静态库/动态库的代码目录(一个动态库/动态库加一个add_subdirectory)

    ```cmake
        add_subdirectory(src/staticLibCode)             # 编译静态库, 在设置的目录中必须有子CMakeLists.txt来设置静态库构建逻辑                      
        add_subdirectory(src/sharedLibCode)             # 编译动态库, 在设置的目录中必须有子CMakeLists.txt来设置动态库构建逻辑
    ``` 

-   第二步 在第一步添加的库代码目录下分别创建子CMakeLists.txt, 并指明要编译的库的名称, 类型和参与编译的源文件
    ```cmake
        # src/staticLibCode目录下的子CMakeLists.txt, 用来编译静态库myMathStatic.a
        add_library(myMathStatic STATIC add.cpp sub.cpp)      
            # myMathStatic      库名称
            # STATIC            指明为静态库
            # add.cpp sub.cpp   指明参与编译库的源代码

        # src/sharedLibCode目录下的子CMakeLists.txt, 用来编译动态库myMathShared.so
        add_library(myMathShared SHARED div.cpp mul.cpp)      
            # myMathShared      库名称
            # SHARED            指明为动态库
            # div.cpp mul.cpp   指明参与编译库的源代码
    ```

**使用静态库**