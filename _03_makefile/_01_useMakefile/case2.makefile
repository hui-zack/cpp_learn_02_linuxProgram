# 方式2 分步编译出可执行文件(.o文件全部生成在执行目录)
useMakefileMain: useMakefileMain.o sub.o add.o
	gcc -o useMakefileMain useMakefileMain.o sub.o add.o

useMakefileMain.o: useMakefileMain.c
	gcc -c useMakefileMain.c

resource/sub.o: resource/sub.c
	gcc -c resource/sub.c

resource/add.o: resource/add.c
	gcc -c resource/add.c

# 优点: 修改一个代码文件时, 只重新编译该文件即可
# 缺点: 编译命令复杂, .o文件全部生成在执行目录, 不美观

#-----------------------------------------------------------------------------------

