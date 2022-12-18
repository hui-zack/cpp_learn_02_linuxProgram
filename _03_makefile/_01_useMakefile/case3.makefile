# 方式3 分步编译出可执行文件, .o文件存放在指定目录
useMakefileMain: complieTmp/useMakefileMain.o complieTmp/sub.o complieTmp/add.o
	gcc -o useMakefileMain complieTmp/useMakefileMain.o complieTmp/sub.o complieTmp/add.o

complieTmp/useMakefileMain.o: useMakefileMain.c
	gcc -c useMakefileMain.c  -o complieTmp/useMakefileMain.o

complieTmp/sub.o: resource/sub.c
	gcc -c resource/sub.c -o complieTmp/sub.o

complieTmp/add.o: resource/add.c
	gcc -c resource/add.c -o complieTmp/add.o

# 优点: 每个代码文件单独编译到complieTmp目录,便于管理, 修改一个代码文件时, 只重新编译该文件即可
# 缺点: 编译命令复杂