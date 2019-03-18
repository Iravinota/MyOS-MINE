/***************************************************
*		版权声明
*
*	本操作系统名为：MINE
*	该操作系统未经授权不得以盈利或非盈利为目的进行开发，
*	只允许个人学习以及公开交流使用
*
*	代码最终所有权及解释权归田宇所有；
*
*	本模块作者：	田宇
*	EMail:		345538255@qq.com
*
*
***************************************************/

#include "font.h"
#include "printk.h"

void Start_Kernel(void)
{
        /*帧缓存物理地址0xe000-0000映射到线性地址0xffff8000-00a00000和0xa0-0000处*/
        int *addr = (int *)0xffff800000a00000;  /*每像素占用32-bit位宽（int）*/
        int i, j;
        int *left_top;
        unsigned char *fontp = font_ascii['A'];
        unsigned char bittest = 0x80;
        unsigned char font_value;

        for (i = 0; i < 1440 * 20; i++)
        {
                *((char *)addr + 0) = (char)0x00;
                *((char *)addr + 1) = (char)0x00;
                *((char *)addr + 2) = (char)0xff;
                *((char *)addr + 3) = (char)0x00;
                addr += 1;      /*addr是int型指针，+1跳过4 bytes*/
        }
        for (i = 0; i < 1440 * 20; i++)
        {
                *((char *)addr + 0) = (char)0x00;
                *((char *)addr + 1) = (char)0xff;
                *((char *)addr + 2) = (char)0x00;
                *((char *)addr + 3) = (char)0x00;
                addr += 1;
        }
        for (i = 0; i < 1440 * 20; i++)
        {
                *((char *)addr + 0) = (char)0xff;
                *((char *)addr + 1) = (char)0x00;
                *((char *)addr + 2) = (char)0x00;
                *((char *)addr + 3) = (char)0x00;
                addr += 1;
        }
        for (i = 0; i < 1440 * 20; i++)
        {
                *((char *)addr + 0) = (char)0xff;
                *((char *)addr + 1) = (char)0xff;
                *((char *)addr + 2) = (char)0xff;
                *((char *)addr + 3) = (char)0x00;
                addr += 1;
        }

        /*Print A*/
        left_top = addr;
        for (i = 0; i < 16; i++) {
                addr = left_top + 1440 * i;
                font_value = fontp[i];
                bittest = 0x80;                 /*10000000b*/
                for (j = 0; j < 8; j++) {
                        if (font_value & bittest) {     /*front color*/
                                *((char *)addr + 0) = (char)0x00;
                                *((char *)addr + 1) = (char)0x00;
                                *((char *)addr + 2) = (char)0xff;
                                *((char *)addr + 3) = (char)0x00;
                        } else {
                                *((char *)addr + 0) = (char)0x00;
                                *((char *)addr + 1) = (char)0xff;
                                *((char *)addr + 2) = (char)0x00;
                                *((char *)addr + 3) = (char)0x00;
                        }
                        addr += 1;
                        bittest = bittest >> 1;
                }
        }

        putchar((unsigned int *)0xffff800000a00000, 1440, 8, 80, 0x00ff0000, 0x0000ff00, 'B');
        

        while (1)
                ;
}