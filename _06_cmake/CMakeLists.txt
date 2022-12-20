# -------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
project(myProject VERSION 1.0 LANGUAGES CXX)            # 设置项目名称, 并指定项目住版本号1, 副版本好0, 执行语言c++

# 打印项目路径
message("|| project dir = " ${CMAKE_SOURCE_DIR})
message("|| build dir = " ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)  # 设置静态库文件输出目录(代码中所有生成的静态库都会到这里)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)  # 设置动态库文件输出目录(代码中所有生成的动态库都会到这里)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)  # 设置可执行文件输出目录(代码中所有生成的可执行文件都会到这里)
set(ME_CONFIG_DIR ${CMAKE_SOURCE_DIR}/config)
set(ME_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

configure_file(${ME_CONFIG_DIR}/config.h.in config.h)                    # 将配置文件config.h.in的内容加载到cmake


# -------------------------------------------------------------------
# debug开关
option(DEBUG_TYPE "set debug" ON)               # 修改该值, 需要使用cmake重新编译项目
if(DEBUG_TYPE) 
    message("|| debug type = true") 
    set(CMAKE_BUILD_TYPE "Debug") 
endif()

# -------------------------------------------------------------------
# 编译自己的库
add_subdirectory(src/myLibrary/staticLibCode)             # 编译静态库, 在设置的目录中必须有子CMakeLists.txt来设置静态库构建逻辑                      
add_subdirectory(src/myLibrary/sharedLibCode)             # 编译动态库, 在设置的目录中必须有子CMakeLists.txt来设置动态库构建逻辑
# -------------------------------------------------------------------
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

FUNC_GETDIRS(SRC_DIRS ${ME_SRC_DIR} "*")                            # 获取src目录的所有子目录, 
FUNC_GETDIRS(STATIC_OUT_DIRS ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} "*") # 获取静态库输出目录的所有子目录

FUNC_GETDIRS(SHARED_OUT_DIRS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} "*") # 获取动态库输出目录的所有子目录
FUNC_GETDIRS(SRC_DIRS ${ME_SRC_DIR} "CMakeLists.txt") 
message("srcdirs = " ${SRC_HEARS})
# -------------------------------------------------------------------
# 编译可执行目标
add_executable(mainDemo src/helloCmake.cpp)     # 设置名称为mainDemo(目标)

FILE(GLOB_RECURSE SRC_HEADERS "*.h")
FILE(GLOB_RECURSE SRC_CPPS "*.cpp")
FILE(GLOB_RECURSE SRC_CS "*.C")


# 为mainDemo目标设置头文件搜索目录
target_include_directories(mainDemo         # 为mainDemo目标设置头文件目录
    PUBLIC                                  # 这些目录下的头文件既能供自己使用, 也可用作外部接口
        ${PROJECT_BINARY_DIR}               # cmake编译目录
        ${STATIC_OUT_DIRS}                  # 静态库输出目录下所有目录
        ${SHARED_OUT_DIRS}                  # 动态库输出目录下所有目录
        ${SRC_DIRS}                         # src下所有目录
    PRIVATE                                 # 这些目录下的头文件只能供自己使用
    INTERFACE                               # 这些目录下的头文件只能用作外部接口
) 

#为mainDemo链接需要用的静态库和动态库(只写库名即可多个库用空格隔开)
target_link_libraries(mainDemo 
    PUBLIC                
        ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libmyMathStatic.a   # 使用的静态库具体到文件名称
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libmyMathShared.so     # 动态库路径只需要具体到目录
)