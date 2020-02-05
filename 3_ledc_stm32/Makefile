objs	:= start.o main.o
ld		:= arm-linux-gnueabihf-ld
gcc		:= arm-linux-gnueabihf-gcc
objcopy	:= arm-linux-gnueabihf-objcopy
objdump	:= arm-linux-gnueabihf-objdump

ledc.bin:$(objs)
	#使用链接脚本文件imx6ul.lds,链接$^(所有依赖文件的集合)，生成ledc.elf
	$(ld) -Timx6ul.lds -o ledc.elf $^
	#将ledc.elf文件转为$@(目标集合),即ledc.bin
	$(objcopy) -O binary -S ledc.elf $@
	#将ledc.elf文件反汇编(arm架构)输出到ledc.dis文件中
	$(objdump) -D -m arm ledc.elf > led.dis

%.o:%.s
	#将所有的.s结尾的文件编译(-Wall:打开所有警告;-nostdlib:不需要启动文件和标准库文件;-O2:优化等级)生成.o文件
	$(gcc) -Wall -nostdlib -c -O2 -o $@ $<

%.o:%.S
	#将所有的.S结尾的文件编译(-Wall:打开所有警告;-nostdlib:不需要启动文件和标准库文件;-O2:优化等级)生成.o文件
	$(gcc) -Wall -nostdlib -c -O2 -o $@ $<

%.o:%.c
	#将所有的.c结尾的文件编译(-Wall:打开所有警告;-nostdlib:不需要启动文件和标准库文件;-O2:优化等级)生成.o文件
	$(gcc) -Wall -nostdlib -c -O2 -o $@ $<

clean:
	rm -rf *.o *.bin *.elf *.dis