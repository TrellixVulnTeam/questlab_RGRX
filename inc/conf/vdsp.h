/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2010-12-10  */
/*     #######          ###    ###      [PORT]      ###  ~~~~~~~~~~~~~~~~~~  */
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
/*  >>>>>>>>>>>>>>>>> CrHack VisualDSP++ 编译器配置头文件 <<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_VDSP_H__
#define __CR_VDSP_H__ 0x8AD5164CUL

/****************************************/
/* 版本值 0x0701010A 表示版本 V7.1.1.10 */
/****************************************/
#if defined(__VISUALDSPVERSION__)

    /* 编译器类型定义 */
    #define _CR_CC_VDSP_
    /*------------------------------------------------*/

    /* 编译器版本定义 */
    #define _CR_CC_VER_     __VERSIONNUM__
    /*------------------------------------------------*/

    /* 编译器名称定义 */
    #if     defined(__ADSPTS__)
        #define _CR_CC_ADSPTS_
        #define _CR_CC_STR_ "VisualDSP++ CCTS"

    #elif   defined(__ADSPBLACKFIN__)
        #define _CR_CC_ADSPBF_
        #define _CR_CC_STR_ "VisualDSP++ CCBLKFN"

    #else
        #define _CR_CC_ADSP21_
        #define _CR_CC_STR_ "VisualDSP++ CC21K"
    #endif
    /*------------------------------------------------*/

    /* 编译器版本过滤 */
    #if     0
        #error "vdsp.h: CC TYPE not supported yet!"
    #endif
    /*------------------------------------------------*/

    /* 编译器平台架构 */
    #if     defined(__ADSPTS__)
        #define _CR_AR_ADSPTS_  /* T-SHARC */
    #elif   defined(__ADSPBLACKFIN__)
        #define _CR_AR_ADSPBF_  /* Blackfin */
    #else
        #define _CR_AR_ADSP21_  /* SHARC-21K */
    #endif
    /*------------------------------------------------*/

    /* 编译器操作系统 */
    #if     1
        #define _CR_OS_NAKED_
    #endif
    /*------------------------------------------------*/

    /* 编译器全局定义 */
    #include <builtins.h>
    /*------------------------------------------------*/

    /* 编译器多余警告 */

    /*------------------------------------------------*/

    /* 编译器内存模型 */
    #if     0
        #define _CR_SMALL_  /* 16bit 小模式 */
    #elif   0
        #define _CR_LARGE_  /* 16bit 巨模式 */
    #endif
    /*------------------------------------------------*/

    /* 编译器过期风格 */
    #if     0
        #define const
        #define signed
        #define volatile
    #endif
    /*------------------------------------------------*/

    /* 编译器特有类型 */
    typedef unsigned int    ubit_t;
    /*------------------------------------------------*/

    /* 编译器指针修饰 */
    #if     1
        #define _far_
        #define _rom_
        #define _slw_
        #define _pge_
        #define _ram_
    #endif
    /*------------------------------------------------*/

    /* 编译器32位浮点 */
    #if     0
        #define _CR_NO_FLT32_
    #endif
    /*------------------------------------------------*/

    /* 编译器64位浮点 */
    #if     0
        #define _CR_NO_FLT64_
    #endif
    /*------------------------------------------------*/

    /* 编译器64位整数 */
    #if     0
        #define _CR_NO_INT64_
    #elif   1
        #define _CR_USE_LLONG_
    #else
        #define _CR_USE_INT64_
    #endif
    /*------------------------------------------------*/

    /* 编译器64位常数后缀 */
    #define CR_SLL(x)   x##LL
    #define CR_ULL(x)   x##ULL
    /*------------------------------------------------*/

    /* 编译器内联函数修饰 */
    #undef  _CR_NO_INLINE_
    #ifndef __cplusplus
        #define inline  __inline
    #endif
    /*------------------------------------------------*/

    /* 编译器汇编内联函数 */
    #define fasm_inline   inline
    /*------------------------------------------------*/

    /* 编译器安全内联函数 */
    #define safe_inline   inline
    /*------------------------------------------------*/

    /* 编译器强迫内联修饰 */
    #define CR_INLINE   _Pragma("always_inline")
    /*------------------------------------------------*/

    /* 编译器函数导出修饰 */
    #if     1
        #define CR_EXPORT
        #define CR_IMPORT
    #endif
    /*------------------------------------------------*/

    /* 编译器内联汇编风格 */
    #if     0
        #define _CR_ASM_INTL_
    #elif   0
        #define _CR_ASM_ATnT_
    #else
        #define _CR_ASM_SPEC_
    #endif
    /*------------------------------------------------*/

    /* 编译器noreturn修饰 */
    #if     1
        #define CR_NORETURN
    #endif
    /*------------------------------------------------*/

    /* 编译器noinline修饰 */
    #if     0
        #define CR_NOINLINE
    #else
        #define CR_NOINLINE _Pragma("never_inline")
    #endif
    /*------------------------------------------------*/

    /* 编译器成员对齐修饰 */
    #if     1
        #define CR_ALIGN(x)
        #define CR_ALIGN01  _Pragma("align 1")
        #define CR_ALIGN02  _Pragma("align 2")
        #define CR_ALIGN04  _Pragma("align 4")
        #define CR_ALIGN08  _Pragma("align 8")
        #define CR_ALIGN16  _Pragma("align 16")
    #endif
    /*------------------------------------------------*/

    /* 编译器导入库的选项 */
    #if     1
        #define _CR_NO_PRAGMA_LIB_
    #endif
    /*------------------------------------------------*/

    /* 编译器紧凑结构修饰 */
    #define CR_PACKED
    #define CR_TYPEDEF  typedef
    #if     0
        #define _CR_NO_PRAGMA_PACK_
    #endif
    /*------------------------------------------------*/

    /* 编译器分支优化指示 */
    #define surely(x)   __builtin_assert(x)
    #define mostly(x)   __builtin_expected_true(x)
    #define rarely(x)   __builtin_expected_false(x)
    /*------------------------------------------------*/

    /* 编译器不支持多线程 */
    #if !defined(_ADI_THREADS) && \
        !defined(__ADI_MULTICORE)
        #define _CR_NO_MT_
    #endif
    /*------------------------------------------------*/

    /* 编译器不支持宽字符 */
    #if     1
        #define _CR_NO_WIDE_
    #endif
    /*------------------------------------------------*/

    /* 编译器指令函数优化 */
    #define _CR_NO_CROT32_
    #define _CR_NO_CROT64_
    #define _CR_NO_IROTSM_
    #ifndef _CR_CC_ADSPBF_
        #define _CR_NO_CSWAP_
        #define _CR_NO_INTRIN_
    #else
        #define _CR_NO_CSWAP64_
    #endif
    #define cr_byteswap16   byteswap2
    #define cr_byteswap32   byteswap4
    /*------------------------------------------------*/

    /* LIBC 剔除所有 C 函数的选项 */
    #if     0
        #define _CR_NO_STDC_
    #endif
    /*------------------------------------------------*/

    /* LIBC 是否支持 GLIBC 函数库 */
    #if     0
        #define _CR_USE_GLIBC_
    #endif
    /*------------------------------------------------*/

    /* LIBC printf() 整数宽度前缀 */
    #define CR_I08
    #define CR_I16
    #define CR_I32
    #define CR_I64  "ll"
    /*------------------------------------------------*/

    /* LIBC 是否有 errno.h 头文件 */
    #if     0
        #define _CR_NO_ERRNO_
    #endif
    /*------------------------------------------------*/

    /* LIBC 支持64位STDIO文件偏移 */
    #if     1
        #define _CR_NO_STDIO64_
    #else
        #define _CR_MS_STDIO64_
    #endif
    /*------------------------------------------------*/

    /* LIBC 支持64位POSIX文件偏移 */
    #if     1
        #define _CR_NO_POSIX64_
    #else
        #define _CR_MS_POSIX64_
    #endif
    /*------------------------------------------------*/

    /* LIBC 支持 C99 数学函数设置 */
    #if     0
        #define _CR_NO_MATHC99_
    #endif
    /*------------------------------------------------*/

    /* LIBC beginthreadex() 返回值 */
    #if     1
        #undef  CR_BTEX_FAIL
    #endif
    /*------------------------------------------------*/

    /* LIBC 支持宽字符串函数的设置 */
    #if     0
        #define _CR_HAVE_WCS_
    #endif
    /*------------------------------------------------*/

    /* 处理器架构的空指令宏设置 */
    #define CR_NOP  asm volatile ("NOP;")
    /*------------------------------------------------*/

    /* 处理器架构的对齐访问设置 */
    #if     1
        #define _CR_ALIGN_NEEDED_
    #endif
    /*------------------------------------------------*/

    /* 处理器架构支持原子级操作 */
    #if     0
        #define _CR_FAST_ATOM_
    #endif
    /*------------------------------------------------*/

#endif  /* __VISUALDSPVERSION__ */

#endif  /* !__CR_VDSP_H__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
