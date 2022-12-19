# 方式4 分步编译出可执行文件, 使用变量简化编译命令



# ##################################################
#    获取当前目录下所有c文件, 并返回list
#    src = ${wildcard *.c}
#
#    把src中的所有c文件的.c后缀修改为.o, 返回list
#    objs = ${patsubst %.c, %.o, ${src}}
#
#    打印变量值
#    ${warning ${srcDir}}
#
#    保留文件名(参数不能为list)
#    filename = $(notdir com/fda.c)
# ####################################################
main = useMakefileMain.c
CC = gcc

targetName = useMakefileMain


od = complieTmp

outputObjs = ${od}/useMakefileMain.o ${od}/sub.o ${od}/add.o



CPPFLAGS = -I ./resource

#${error ${mainO}}


${targetName}: ${outputObjs}
	${CC} $^ ${CPPFLAGS} -o useMakefileMain


# main函数的.o编译
${od}/useMakefileMain.o: ${main}
	${CC} -g -c ${main}  -o ${od}/useMakefileMain.o

# resource目录的.o编译
${od}/%.o: resource/%.c
	${CC} -g -c $^ -o $@

#清理命令
clear:
	rm ${od}/*.o
