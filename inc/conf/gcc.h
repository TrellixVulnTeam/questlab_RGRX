/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2010-04-17  */
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
/*  >>>>>>>>>>>>>>>>>> CrHack GNU C/C++ 编译器配置头文件 <<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_GCC_H__
#define __CR_GCC_H__

/****************************************/
/* 考虑到 GCC 可能有多种平台的兼容版本  */
/* 所以其配置头文件放到头文件列表的最后 */
/****************************************/
#if defined(__GNUC__)

    /* 编译器类型定义 */
    #define _CR_CC_GCC_
    /*------------------------------------------------*/

    /* 编译器版本定义 */
    #ifndef __GNUC_PATCHLEVEL__
        #define _CR_CC_VER_ (__GNUC__ * 10000 + \
                             __GNUC_MINOR__ * 100)
    #else
        #define _CR_CC_VER_ (__GNUC__ * 10000 + \
                             __GNUC_MINOR__ * 100 + \
                             __GNUC_PATCHLEVEL__)
    #endif
    /*------------------------------------------------*/

    /* 编译器名称定义 */
    #if     defined(__MINGW64__)
        #define _CR_CC_MINGW_
        #define _CR_CC_MINGW64_
        #define _CR_CC_STR_     "GCC (MinGW64)"

    #elif   defined(__MINGW32__)
        #define _CR_CC_MINGW_
        #define _CR_CC_MINGW32_
        #define _CR_CC_STR_     "GCC (MinGW32)"

    #elif   defined(__GO32__) || \
            defined(__DJGPP__)
        #define _CR_CC_DJGPP_
        #define _CR_CC_STR_     "GCC (DJGPP)"

    #elif   defined(__CYGWIN__)
        #define _CR_CC_CYGWIN_
        #define _CR_CC_STR_     "GCC (Cygwin)"

    #else
        #define _CR_CC_STR_     "GCC (GNU)"
    #endif
    /*------------------------------------------------*/

    /* 编译器版本过滤 */
    #if (_CR_CC_VER_ < 20700)
        #error "gcc.h: CC TYPE not supported yet!"
    #endif
    /*------------------------------------------------*/

    /* 编译器平台架构 */
    #if     defined(__amd64) || defined(__amd64__) || \
            defined(__x86_64) || defined(__x86_64__)
        #define _CR_AR_X64_     /* AMD64 & EM64T */

    #elif   defined(i386) || defined(__i386) || \
            defined(__i386__) || defined(_X86_)
        #define _CR_AR_X86_     /* Intel X86 */

    #elif   defined(__thumb) || defined(__thumb__)
        #define _CR_AR_THUMB_   /* THUMB */

    #elif   defined(__arm) || defined(__arm__)
        #define _CR_AR_ARM_     /* ARM */

    #elif   defined(mips) || defined(__mips__)
        #define _CR_AR_MIPS_    /* MIPS */

    #elif   defined(__ppc__) || defined(__powerpc) || \
            defined(__powerpc__) || defined(__POWERPC__)
        #define _CR_AR_PPC_     /* PowerPC */

    #elif   defined(__sparc__)
        #define _CR_AR_SPARC_   /* SPARC */

    #elif   defined(__sh__)
        #define _CR_AR_SH_      /* SuperH */

    #elif   defined(__m68k__)
        #define _CR_AR_68K_     /* M68000 */

    #elif   defined(__ia64__) || \
            defined(_IA64) || defined(__IA64__)
        #define _CR_AR_IA64_    /* IA64 */

    #elif   defined(__hppa__) || defined(__hppa)
        #define _CR_AR_HPPA_    /* HP/PA RISC */

    #elif   defined(__alpha__)
        #define _CR_AR_ALPHA_   /* Alpha AXP */

    #elif   defined(__ADSPBLACKFIN__) || \
            defined(__bfin) || defined(__bfin__) || \
            defined(__BFIN) || defined(__BFIN__)
        #define _CR_AR_ADSPBF_  /* Blackfin */
    #else
        #error "gcc.h: AR TYPE not supported yet!"
    #endif
    /*------------------------------------------------*/

    /* 编译器操作系统 */
    #if     defined(_WIN32_WCE)
        #define _CR_OS_MSWIN_
        #define _CR_OS_WINCE_

    #elif   defined(WIN32) || defined(_WIN32) || \
            defined(__WIN32) || defined(__WIN32__)
        #define _CR_OS_MSWIN_
        #define _CR_OS_WIN32_

    #elif   defined(MSDOS) || defined(__MSDOS) || \
            defined(__MSDOS__)
        #define _CR_OS_DOS32_

    /* *NIX 操作系统必须放在最后 */
    #elif   defined(unix) || defined(__unix) || \
            defined(__unix__) || defined(linux) || \
            defined(__linux) || defined(__linux__)
        #define _CR_OS_UNIX_

        #if defined(linux) || defined(__linux) || \
            defined(__linux__)
            #define _CR_OS_LINUX_
        #endif
    #else
        #define _CR_OS_NAKED_   /* 最后是裸机 */
    #endif
    /*------------------------------------------------*/

    /* 编译器全局定义 */
    #if defined(_CR_OS_WIN32_)
        /* 解决函数定义丢失的问题 (Win2000+) */
        #if     !defined(WINVER)
            #define WINVER  0x0500
        #elif   (WINVER < 0x0500)
            #undef  WINVER
            #define WINVER  0x0500
        #endif
        /* 解决结构体找不到的问题 (Win2000+) */
        #if     !defined(_WIN32_WINNT)
            #define _WIN32_WINNT    0x0500
        #elif   (_WIN32_WINNT < 0x0500)
            #undef  _WIN32_WINNT
            #define _WIN32_WINNT    0x0500
        #endif
    #endif
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
        #define _slw_
        #define _pge_
        #define _ram_
        #define _rom_
        #define _far_
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
        #define inline  static __inline
    #endif
    /*------------------------------------------------*/

    /* 编译器汇编内联函数 */
    #define fasm_inline     inline
    /*------------------------------------------------*/

    /* 编译器安全内联函数 */
    #define safe_inline     inline
    /*------------------------------------------------*/

    /* 编译器强迫内联修饰 */
    #define CR_INLINE   __attribute__((always_inline))
    /*------------------------------------------------*/

    /* 编译器函数导出修饰 */
    #ifndef _CR_OS_MSWIN_
        #define CR_EXPORT
        #define CR_IMPORT
    #else
        #define CR_EXPORT   __attribute__((dllexport))
        #define CR_IMPORT   __attribute__((dllimport))
    #endif
    /*------------------------------------------------*/

    /* 编译器内联汇编风格 */
    #if     0
        #define _CR_ASM_INTL_
    #elif   1
        #define _CR_ASM_ATnT_
    #else
        #define _CR_ASM_SPEC_
    #endif
    /*------------------------------------------------*/

    /* 编译器noreturn修饰 */
    #if     0
        #define CR_NORETURN
    #else
        #define CR_NORETURN __attribute__((noreturn))
    #endif
    /*------------------------------------------------*/

    /* 编译器noinline修饰 */
    #if     0
        #define CR_NOINLINE
    #else
        #define CR_NOINLINE __attribute__((noinline))
    #endif
    /*------------------------------------------------*/

    /* 编译器成员对齐修饰 */
    #if     0
        #define CR_ALIGN(x)
    #else
        #define CR_ALIGN(x) __attribute__((aligned(x)))
    #endif
    /*------------------------------------------------*/

    /* 编译器导入库的选项 */
    #if     1
        #define _CR_NO_PRAGMA_LIB_
    #endif
    /*------------------------------------------------*/

    /* 编译器紧凑结构修饰 */
    #define CR_TYPEDEF  typedef
    #define CR_PACKED   __attribute__((packed))
    #if     1
        #define _CR_NO_PRAGMA_PACK_
    #endif
    /*------------------------------------------------*/

    /* 编译器分支优化指示 */
    #if (_CR_CC_VER_ < 20900)
        #define surely(x)   (x)
        #define mostly(x)   (x)
        #define rarely(x)   (x)
    #else
        #define surely(x)   (x)
        #define mostly(x)   __builtin_expect(!!(x), 1)
        #define rarely(x)   __builtin_expect(!!(x), 0)
    #endif
    /*------------------------------------------------*/

    /* 编译器不支持多线程 */
    #if defined(_CR_OS_DOS32_) || \
        defined(_CR_OS_NAKED_)
        #define _CR_NO_MT_
    #endif
    /*------------------------------------------------*/

    /* 编译器不支持宽字符 */
    #if     0
        #define _CR_NO_WIDE_
    #endif
    /*------------------------------------------------*/

    /* 编译器指令函数优化 */
    #define _CR_NO_CSWAP_
    #define _CR_NO_CROT32_
    #define _CR_NO_CROT64_
    #define _CR_NO_IROTSM_
    #define _CR_NO_INTRIN_
    /*------------------------------------------------*/

    /* LIBC 剔除所有 C 函数的选项 */
    #if     0
        #define _CR_NO_STDC_
    #endif
    /*------------------------------------------------*/

    /* LIBC 是否支持 GLIBC 函数库 */
    #if defined(_CR_OS_UNIX_)
        #define _CR_USE_GLIBC_
    #endif
    /*------------------------------------------------*/

    /* LIBC printf() 整数宽度前缀 */
    #define CR_I08
    #define CR_I16
    #define CR_I32
    #ifndef _CR_CC_MINGW_
        #define CR_I64  "ll"
    #else
        #define CR_I64  "I64"
    #endif
    /*------------------------------------------------*/

    /* LIBC 是否有 errno.h 头文件 */
    #if defined(_CR_OS_WINCE_)
        #define _CR_NO_ERRNO_
    #endif
    /*------------------------------------------------*/

    /* LIBC 支持64位STDIO文件偏移 */
    #if defined(_CR_OS_DOS32_) || \
        defined(_CR_OS_MSWIN_)
        #define _CR_NO_STDIO64_
    #elif   0
        #define _CR_MS_STDIO64_
    #endif
    /*------------------------------------------------*/

    /* LIBC 支持64位POSIX文件偏移 */
    #if defined(_CR_OS_DOS32_) || \
        defined(_CR_OS_MSWIN_)
        #define _CR_NO_POSIX64_
    #elif   0
        #define _CR_MS_POSIX64_
    #endif
    /*------------------------------------------------*/

    /* LIBC 支持 C99 数学函数设置 */
    #if     0
        #define _CR_NO_MATHC99_
    #endif
    /*------------------------------------------------*/

    /* LIBC beginthreadex() 返回值 */
    #if !defined(_CR_NO_STDC_) && \
         defined(_CR_OS_MSWIN_)
        #define CR_BTEX_FAIL    0
    #endif
    /*------------------------------------------------*/

    /* LIBC 支持宽字符串函数的设置 */
    #if !defined(_CR_NO_STDC_) && \
         defined(_CR_OS_MSWIN_)
        #define _CR_HAVE_WCS_
    #endif
    /*------------------------------------------------*/

    /* 处理器架构的空指令宏设置 */
    #define CR_NOP  __asm__("nop")
    /*------------------------------------------------*/

    /* 处理器架构的对齐访问设置 */
    #if !defined(_CR_AR_X86_) && \
        !defined(_CR_AR_X64_)   /* maybe more */
        #define _CR_ALIGN_NEEDED_
    #endif
    /*------------------------------------------------*/

    /* 处理器架构支持原子级操作 */
    #if     0
        #define _CR_FAST_ATOM_
    #endif
    /*------------------------------------------------*/

#endif  /* __GNUC__ */

#endif  /* !__CR_GCC_H__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
