/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2011-09-06  */
/*     #######          ###    ###      [KRNL]      ###  ~~~~~~~~~~~~~~~~~~  */
/*    ########          ###    ###                  ###  MODIFY: XXXX-XX-XX  */
/*    ####  ##          ###    ###                  ###  ~~~~~~~~~~~~~~~~~~  */
/*   ###       ### ###  ###    ###    ####    ####  ###   ##  +-----------+  */
/*  ####       ######## ##########  #######  ###### ###  ###  |  A NEW C  |  */
/*  ###        ######## ########## ########  ###### ### ###   | FRAMEWORK |  */
/*  ###     ## #### ### ########## ###  ### ###     ######    |  FOR ALL  |  */
/*  ####   ### ###  ### ###    ### ###  ### ###     ######    | PLATFORMS |  */
/*  ########## ###      ###    ### ######## ####### #######   |  AND ALL  |  */
/*   #######   ###      ###    ### ########  ###### ###  ###  | COMPILERS |  */
/*    #####    ###      ###    ###  #### ##   ####  ###   ##  +-----------+  */
/*  =======================================================================  */
/*  >>>>>>>>>>>>>>>>>> CrHack XICOR X5XXX 器件定义头文件 <<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_X5XXX_H__
#define __CR_X5XXX_H__

#include "../defs.h"

/* X5XXX 状态寄存器位值 */
#define X5XXX_WIP       0x01    /* 是否正在写数据 */
#define X5XXX_WEL       0x02    /* 是否可以写数据 */
#define X5XXX_P_NONE    0x00    /* 芯片数据无保护 */
#define X5XXX_P_QUAD    0x04    /* 芯片数据1/4保护 */
#define X5XXX_P_HALF    0x08    /* 芯片数据1/2保护 */
#define X5XXX_P_FULL    0x0C    /* 芯片数据全保护 */
#define X5XXX_W_1400    0x00    /* 看门狗 1.4s 溢出 */
#define X5XXX_W_0600    0x10    /* 看门狗 600ms 溢出 */
#define X5XXX_W_0200    0x20    /* 看门狗 200ms 溢出 */
#define X5XXX_W_NONE    0x30    /* 看门狗的功能关闭 */
#define X5XXX_FLB       0x40    /* 上电丢失的标志位 */
#define X5XXX_WPEN      0x80    /* 状态寄存器写保护 */

/* X5083 状态寄存器位值 */
#define X5083_P_NO      0x00    /* 芯片数据无保护 */
#define X5083_P_Q1      0x01    /* 芯片保护000h-0FFh */
#define X5083_P_Q2      0x02    /* 芯片保护100h-1FFh */
#define X5083_P_Q3      0x03    /* 芯片保护200h-2FFh */
#define X5083_P_Q4      0x04    /* 芯片保护300h-3FFh */
#define X5083_P_H1      0x05    /* 芯片保护000h-1FFh */
#define X5083_P_P0      0x06    /* 芯片保护000h-00Fh */
#define X5083_P_PN      0x07    /* 芯片保护3F0h-3FFh */
#define X5083_W_1400    0x00    /* 看门狗 1.4s 溢出 */
#define X5083_W_0600    0x08    /* 看门狗 600ms 溢出 */
#define X5083_W_0200    0x10    /* 看门狗 200ms 溢出 */
#define X5083_W_NONE    0x18    /* 看门狗的功能关闭 */

#endif  /* !__CR_X5XXX_H__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
