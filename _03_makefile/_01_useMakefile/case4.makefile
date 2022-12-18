
# 方式4 分步编译出可执行文件, .o文件存放在指定目录
main = useMakefileMain.c
CC = gcc

targetName = useMakefileMain
outputObjs = complieTmp/useMakefileMain.o complieTmp/sub.o complieTmp/add.o

od = complieTmp

CPPFLAGS = -I ./resource

${targetName}: ${outputObjs}
	${CC} -o useMakefileMain $^ ${CPPFLAGS}


${od}/useMakefileMain.o: ${main}
	${CC} -c ${main}  -o ${od}/useMakefileMain.o


${od}/%.o: resource/%.c
	${CC} -c $^ -o $@
