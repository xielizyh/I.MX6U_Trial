# ?= 表示如果变量前面没有赋值，使用新值，否则使用前面值
# 定义交叉编译变量
CROSS_COMPILE	?= arm-linux-gnueabihf-
# 定义目标变量
TARGET			?= printf

# := 表示只能使用前面定义好的值，即使后面重新赋值，也不更新
# 定义编译变量
CC				:= $(CROSS_COMPILE)gcc
# 定义链接变量
LD				:= $(CROSS_COMPILE)ld
# 定义格式转换变量
OBJCOPY			:= $(CROSS_COMPILE)objcopy
# 定义反汇编变量
OBJDUMP			:= $(CROSS_COMPILE)objdump

# 定义库文件目录变量
LIBPATH			:= -lgcc -L /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4

# 定义头文件目录变量
INCDIRS			:=	project \
					imx6u \
					stdio/include \
					bsp/clk \
					bsp/delay \
					bsp/led \
					bsp/beep \
					bsp/gpio \
					bsp/key \
					bsp/int \
					bsp/exit \
					bsp/epit \
					bsp/uart

# 定义源文件目录变量
SRCDIRS			:=	project \
					imx6u \
					stdio/lib \
					bsp/clk \
					bsp/delay \
					bsp/led \
					bsp/beep \
					bsp/gpio \
					bsp/key \
					bsp/int \
					bsp/exit \
					bsp/epit \
					bsp/uart

# patsubst:模式字符串替换函数;将INCDIRS添加-I字符串;指定文件目录时需要加上"-I"
INCLUDE			:= $(patsubst %, -I %, $(INCDIRS))

# 定义所有的.S汇编文件变量(包括绝对路径)；wildcard: 让通配符在变量中可以展开
SFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))

# 定义所有的.c文件变量(包括绝对路径)；wildcard: 让通配符在变量中可以展开
CFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

# 定义所有的.S文件变量
SFILENDIR		:= $(notdir $(SFILES))

# 定义所有的.c文件变量
CFILENDIR		:= $(notdir $(CFILES))

# 定义所有的.S文件生成的.o文件目录变量;$(SFILENDIR:.S=.o):将.S结尾的字串替换成.o
SOBJS			:= $(patsubst %, obj/%, $(SFILENDIR:.S=.o))

# 定义所有的.c文件生成的.o文件目录变量;$(SFILENDIR:.c=.o):将.c结尾的字串替换成.o
COBJS			:= $(patsubst %, obj/%, $(CFILENDIR:.c=.o))

# 定义所有.o文件目录变量
OBJS			:= $(SOBJS) $(COBJS)

# 特殊变量;make先在当前目录寻找依赖文件和目标文件，搜索不到则去VPATH指定的目录寻找
VPATH			:= $(SRCDIRS)

# 伪目标 解决存在文件重名，即为clean文件
.PHONY: clean

# 链接生成.elf文件，将.elf文件转换为.bin文件，反汇编生成.dis文件
$(TARGET).bin : $(OBJS)
	$(LD) -Timx6ul.lds -o $(TARGET).elf $^ $(LIBPATH)
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

# 静态模式 将所有的.S文件编译成.o,并存入到obj目录下
$(SOBJS) : obj/%.o : %.S
	$(CC) -Wall -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<

# 静态模式 将所有的.S文件编译成.o,并存入到obj目录下
$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<

# 清理工程规则
clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(COBJS) $(SOBJS) 

print:
	@echo CROSS_COMPILE: 	$(CROSS_COMPILE)
	@echo TARGET: 			$(TARGET)
	@echo CC: 				$(CC)
	@echo LD: 				$(LD)
	@echo OBJCOPY: 			$(OBJCOPY)
	@echo OBJDUMP: 			$(OBJDUMP)
	@echo INCDIRS: 			$(INCDIRS)
	@echo SRCDIRS: 			$(SRCDIRS)
	@echo INCLUDE: 			$(INCLUDE)
	@echo SFILES: 			$(SFILES)
	@echo CFILES: 			$(CFILES)
	@echo SFILENDIR: 		$(SFILENDIR)
	@echo CFILENDIR: 		$(CFILENDIR)
	@echo SOBJS: 			$(SOBJS)
	@echo COBJS: 			$(COBJS)
	@echo OBJS: 			$(OBJS)

