#定义变量objs
objs := start.o main.o

#默认目标
ledc.bin:$(objs)
	#链接$^(所有依赖文件的集合)到起始地址0x87800000，生成ledc.elf
	arm-linux-gnueabihf-ld -Ttext 0x87800000 -o ledc.elf $^
	#将ledc.elf文件转为$@(目标集合),即ledc.bin
	arm-linux-gnueabihf-objcopy -O binary -S ledc.elf $@
	#将ledc.elf文件反汇编(arm架构)输出到ledc.dis文件中
	arm-linux-gnueabihf-objdump -D -m arm ledc.elf > ledc.dis

%.o:%.s
	#将所有的.s结尾的文件编译(-Wall:打开所有警告;-nostdlib:不需要启动文件和标准库文件;-O2:优化等级)生成.o文件
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o $@ $<

%.o:%.S
	#将所有的.s结尾的文件编译(-Wall:打开所有警告;-nostdlib:不需要启动文件和标准库文件;-O2:优化等级)生成.o文件
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o $@ $<

%.o:%.c
	#将所有的.s结尾的文件编译(-Wall:打开所有警告;-nostdlib:不需要启动文件和标准库文件;-O2:优化等级)生成.o文件
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o $@ $<

clean:
	rm -rf *.o *.bin *.elf *.dis