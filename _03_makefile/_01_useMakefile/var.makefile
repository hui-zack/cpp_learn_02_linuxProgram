# 本文件只展示makefile的变量如何定义和设置, 不能复制到makefile里参加编译
# 1-1 makefile普通变量

	# 1-1-1 定义普通变量
	var1 = resource

	# 1-1-2 使用普通变量
	result = ${var1}

# ---------------------------------------------

# 1-2 makefile系统变量
	# 1-2-1 指定系统类型的变量 CC
	CC = gcc
	CC = g++

	# 1-2-2 指定头文件目录的系统变量(设置gcc的-I) CPPFLAGS
	CPPFLAGS = -I ./resource

	# 1-2-3 指定编译方式的系统变量(选择设置gcc的-c, -S, -E, -WAll -g) CFLAGS
	CFLAGS = -c

	# 1-2-4 指定库文件的系统变量(设置gcc的-L, -l) LDFLAGS
	LDFLAGS = **

# -------------------------------------------

# 1-3 makefile中的自动变量(只能用在命令中)
	# 自动变量中的规则: 规则指的依赖行, 如 main : add.o sub.o
	# 	规则目标		$@ = main
	# 	规则列表		$^ = add.o sub.o, add.o就是
	# 	第一个条件	$< = add.o

	# 1-3-1 表示规则中的目标 $@
	# 1-3-3 表示所有规则的列表, 以空格分割(自动删除重复项) $^
	# 1-3-2 表示规则列表的第一个条件 $<









# 结束(下面这句是为了过makefile的语法检查, 没有实际意义)
	result1 = true

