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

void Start_Kernel(void)
{
        /*帧缓存物理地址0xe000-0000映射到线性地址0xffff8000-00a00000和0xa0-0000处*/
        int *addr = (int *)0xffff800000a00000;  /*每像素占用32-bit位宽（int）*/
        int i;

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

        while (1)
                ;
}