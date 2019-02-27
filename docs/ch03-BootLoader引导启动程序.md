# 第3章-BootLoader引导启动程序

有一些书上讲的不是很明白的地方，需要补充一下。

## 1. 计算机加电启动过程

参考资料：<http://www.brokenthorn.com/Resources/OSDevIndex.html>

1. 按电脑的电源键
2. 产生一个电信号，此电信号传送到主板，告知主板启动电脑
3. 主板把这个电信号告知电源（PSU, Power SUpply），要启动电脑
4. 电源开始给主板以及所有周边设备供电
5. 等电压稳定后，电源产生一个电信号，告知主板，电源供应稳定
6. 主板开始执行POST(Power On Self Test)，检测硬件是否都正常
7. CPU到0xFFF0地址执行第一条BIOS指令。32位计算机的地址空间为0x00000000 - 0xffffffff，对于RAM和ROM(存放着BIOS)，可以被CPU映射到这个地址空间的任意位置。一般情况下，RAM被映射到0x00000000开始的位置，而ROM则被映射到以0xffffffff结束的位置。CPU每次被reset时，都会固定到0xfffffff0处去执行指令，这也就是BIOS所在的位置（不是BIOS的起始位置，是BIOS中一条指令的位置）。CPU启动时，处于16位real mode，可用的地址线只有20位，是无法寻址到0xfffffff0这个位置的。但是为了向下兼容，现在的CPU很可能做了一些特殊处理，比如把高12位地址线全部置为1。这样，ip=0x0000fff0时，其实寻址的位置就是0xfffffff0。使用Bochs模拟的结果如下：

![bochs bios start](img/2019-02-27-21-19-33.png)

8. BIOS在内存中创建IVT（Interrupt Vector Table），用于执行中断。当CPU芯片上有中断信号到达时，在CPU完成当前指令之后，就会根据IVT执行对应的中断处理程序。IVT被放置在物理内存的最开始位置，从0x0000到0x03ff，一共1024字节，共256项，每项占4个字节，指向IR(Interrupt Routine)所在的地址。
9. BIOS做一些更多的硬件检测，看看硬件是否都正常。
10. BIOS按照设置的设备启动顺序，依次检测这些设备是不是可启动设备。如果一个设备（磁盘、软盘、U盘、光盘等）的第一个sector的第511字节是0x55，第512字节是0xAA，那么这个设备就是一个可启动设备。
11. BIOS把可启动设备的bootable sector加载到0x7c00地址处。CPU跳转到0x7c00处开始执行启动程序（也就是第3章编写的boot.asm编译之后的程序）。以上5步为BIOS的执行。
12. *持续更新*

## 2. 通用寄存器

![General Purpose Register](img/2019-02-26-23-43-06.png)

![useful for gpr](img/2019-02-26-23-44-59.png)

## 3. 段寄存器

- Used in Real Mode:

![Segment Register](img/2019-02-26-23-46-49.png)

- Used in Protected Mode:

![Segment Register](img/2019-02-26-23-49-58.png)

## 4. 内存使用情况

![memory model](img/2019-02-27-21-22-36.png)

详细情况请参看[Memory Map](https://wiki.osdev.org/Memory_Map_(x86))

## 4. NASM指令参考

参考[这里](https://www.nasm.us/doc/)

- 十六进制数值常量：0x1f2f, 1f2fh. 参看[这里](https://www.nasm.us/doc/nasmdoc3.html#section-3.4.1)

## 5. 创建虚拟软盘

`bximage`执行之后，会在**当前目录**创建一个boot.img文件，Bochs会使用这个文件作为floppya。所以，我们要在Bochs目录（~/Software/bochs-2.6.8）中执行此命令。在Bochs目录下，.bochsrc中，需要有`floppya: image="boot.img", status=inserted`设置。

``` bash
[eric@study /media/sf_LinuxShareFolder/MyOS_MINE/code]$ l
total 4
-rwxrwxrwx. 1 root root 907 Feb 27 00:06 boot.asm
[eric@study /media/sf_LinuxShareFolder/MyOS_MINE/code]$ nasm boot.asm -o boot.bin
[eric@study /media/sf_LinuxShareFolder/MyOS_MINE/code]$ dd if=boot.bin of=/home/eric/Software/bochs-2.6.8/boot.img bs=512 count=1 conv=notrunc
1+0 records in
1+0 records out
512 bytes (512 B) copied, 0.000302191 s, 1.7 MB/s
```

## 6. Bochs设置

- 注释掉 sound, ata0-master
- 启动bochs时可以直接执行`bochs`命令，默认加载.bochsrc配置文件。书中启动的命令不对。

## 7. 书中3.1.2节中代码解释

`jmp $` 表示无限循环。

## 8. FAT12文件系统

参看[An overview of FAT12](http://www.disc.ua.es/~gil/FAT12Description.pdf)

参看[FAT12文件系统简介](https://blog.csdn.net/xhyzjiji/article/details/49027013)

参看[FAT File Systems](http://www.ntfs.com/fat-systems.htm)