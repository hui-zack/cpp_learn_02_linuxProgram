# 方式1 一步编译可执行文件
useMakefileMain: useMakefileMain.c resource/add.c resource/sub.c
	gcc -o useMakefileMain  useMakefileMain.c resource/add.c resource/sub.c

# 优点: 一步编译, 没有过程文件
# 缺点: 若修改一个文件的代码, 所有文件都要重新编译