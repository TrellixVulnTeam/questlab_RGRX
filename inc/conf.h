/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2009-12-15  */
/*     #######          ###    ###      [PORT]      ###  ~~~~~~~~~~~~~~~~~~  */
/*    ########          ###    ###                  ###  MODIFY: 2013-05-28  */
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
/*  >>>>>>>>>>>>>>>>>>>>>>>> CrHack 公用配置头文件 <<<<<<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_CONF_H__
#define __CR_CONF_H__ 0xEC610E9EUL

/*****************************************************************************/
/*                               编译器的配置                                */
/*****************************************************************************/

/* 编译器配置列表 */
#ifndef _CR_CC_VER_
    #include "conf/bcc.h"
#endif
#ifndef _CR_CC_VER_
    #include "conf/msc.h"
#endif
#ifndef _CR_CC_VER_
    #include "conf/cx51.h"
#endif
#ifndef _CR_CC_VER_
    #include "conf/armcc.h"
#endif
#ifndef _CR_CC_VER_
    #include "conf/iarcc.h"
#endif
#ifndef _CR_CC_VER_
    #include "conf/vdsp.h"
#endif
#ifndef _CR_CC_VER_
    #include "conf/gcc.h"
#endif

/* 不支持编译器或配置错误 */
#if !defined(_CR_CC_VER_) || \
    !defined(_CR_CC_STR_)
    #error "conf.h: CC TYPE not supported yet!"
#endif

/*****************************************************************************/
/*                               平台架构配置                                */
/*****************************************************************************/

/* Intel X86
  (16bit/32bit Little-Endian) */
#if     defined(_CR_AR_X86_)
    #define _CR_ORDER_LE_
    #define _CR_AR_STR_ "[X86]"

/* AMD64 & EM64T
  (64bit Little-Endian) */
#elif   defined(_CR_AR_X64_)
    #define _CR_SYS64_
    #define _CR_ORDER_LE_
    #define _CR_AR_STR_ "[X64]"

/* ARM
  (32bit Bi-Endian) */
#elif   defined(_CR_AR_ARM_)
    #define _CR_SYS32_
    #define _CR_AR_STR_ "[ARM]"

/* THUMB
  (32bit Bi-Endian) */
#elif   defined(_CR_AR_THUMB_)
    #define _CR_SYS32_
    #define _CR_AR_STR_ "[THUMB]"

/* MIPS
  (32bit/64bit Bi-Endian) */
#elif   defined(_CR_AR_MIPS_)
    #define _CR_AR_STR_ "[MIPS]"

    /* 系统位数 */
    #ifdef  __mips64
        #define _CR_SYS64_
    #endif

    /* 字节顺序 */
    #if     defined(__MIPSEL__)
        #define _CR_ORDER_LE_
    #elif   defined(__MIPSEB__)
        #define _CR_ORDER_BE_
    #endif

/* PowerPC
  (32bit/64bit Big-Endian) */
#elif   defined(_CR_AR_PPC_)
    #define _CR_ORDER_BE_
    #define _CR_AR_STR_ "[PPC]"

/* MOTO 68000
  (32bit Big-Endian) */
#elif   defined(_CR_AR_68K_)
    #define _CR_SYS32_
    #define _CR_ORDER_BE_
    #define _CR_AR_STR_ "[68K]"

/* SuperH
  (32bit/64bit Bi-Endian) */
#elif   defined(_CR_AR_SH_)
    #define _CR_AR_STR_ "[SH]"

/* SPARC
  (32bit/64bit Big-Endian) */
#elif   defined(_CR_AR_SPARC_)
    #define _CR_AR_STR_ "[SPARC]"

    /* 字节顺序 */
    #define _CR_ORDER_BE_

    /* 系统位数 */
    #if     defined(__sparcv8)
        #define _CR_SYS32_
    #elif   defined(__sparcv9)
        #define _CR_SYS64_
    #endif

/* IA64
  (64bit Bi-Endian) */
#elif   defined(_CR_AR_IA64_)
    #define _CR_SYS64_
    #define _CR_AR_STR_ "[IA64]"

/* Alpha AXP
  (64bit Little-Endian) */
#elif   defined(_CR_AR_ALPHA_)
    #define _CR_SYS64_
    #define _CR_ORDER_LE_
    #define _CR_AR_STR_ "[ALPHA]"

/* HP/PA RISC
  (32bit/64bit Bi-Endian) */
#elif   defined(_CR_AR_HPPA_)
    #define _CR_AR_STR_ "[HPPA]"

/* RS/6000
  (32bit/64bit Bi-Endian) */
#elif   defined(_CR_AR_RS6K_)
    #define _CR_AR_STR_ "[RS6K]"

/* System/370
  (32bit Big-Endian) */
#elif   defined(_CR_AR_S370_)
    #define _CR_SYS32_
    #define _CR_ORDER_BE_
    #define _CR_AR_STR_ "[S370]"

/* System/390
  (32bit/64bit Big-Endian) */
#elif   defined(_CR_AR_S390_)
    #define _CR_AR_STR_ "[S390]"

    /* 字节顺序 */
    #define _CR_ORDER_BE_

    /* 系统位数 */
    #if     defined(__s390__)
        #define _CR_SYS32_
    #elif   defined(__s390x__)
        #define _CR_SYS64_
    #endif

/* z/Architecture
  (64bit Big-Endian) */
#elif   defined(_CR_AR_ZARCH_)
    #define _CR_SYS64_
    #define _CR_ORDER_BE_
    #define _CR_AR_STR_ "[ZARCH]"

/* Intel MCS-51
  (8bit Compiler-Endian) */
#elif   defined(_CR_AR_MCS51_)
    #define _CR_SYS16_
    #define _CR_ARCH8_
    #define _CR_AR_STR_ "[MCS51]"

/* ADSP Blackfin
  (32bit Little-Endian) */
#elif   defined(_CR_AR_ADSPBF_)
    #define _CR_SYS32_
    #define _CR_ORDER_LE_
    #define _CR_AR_STR_ "[ADSP-BF]"

/* ADSP SHARC 21K
  (32bit Little-Endian) */
#elif   defined(_CR_AR_ADSP21_)
    #define _CR_SYS32_
    #define _CR_ORDER_LE_
    #define _CR_AR_STR_ "[ADSP-21]"

/* ADSP TigerSHARC
  (32bit Little-Endian) */
#elif   defined(_CR_AR_ADSPTS_)
    #define _CR_SYS32_
    #define _CR_ORDER_LE_
    #define _CR_AR_STR_ "[ADSP-TS]"

#endif  /* AR TYPE predefines */

/* 使用额外的宏识别系统位数 */
#if !defined(_CR_SYS16_) && \
    !defined(_CR_SYS32_) && \
    !defined(_CR_SYS64_)

    /* 16bit 操作系统和编译器 */
    #if     defined(_CR_OS_DOS16_) || \
            defined(_CR_OS_WIN16_)
        #define _CR_SYS16_

    /* 64bit 操作系统和编译器 */
    #elif   defined(_CR_OS_WIN64_) || \
            defined(_LP64) || defined(__LP64__) || \
            defined(__64BIT__) || defined(__arch64) || \
            defined(__arch64__)
        #define _CR_SYS64_

    /* 32bit 操作系统和编译器 */
    #else
        #define _CR_SYS32_      /* (默认) */
    #endif
#endif  /* !_CR_SYS16_ && !_CR_SYS32_ && !_CR_SYS64_ */

/* 过滤非法的系统位数定义 */
#if     defined(_CR_SMALL_) && !defined(_CR_SYS16_)
    #error "conf.h: invalid _CR_SMALL_ define!"
#elif   defined(_CR_LARGE_) && !defined(_CR_SYS16_)
    #error "conf.h: invalid _CR_LARGE_ define!"
#endif

/* 使用额外的宏识别字节顺序 */
#if !defined(_CR_ORDER_LE_) && !defined(_CR_ORDER_BE_)
    #if     defined(_LITTLE_ENDIAN) || defined(__LITTLE_ENDIAN) || \
            defined(__LITTLE_ENDIAN__) || defined(__little_endian__)
        #define _CR_ORDER_LE_

    #elif   defined(_BIG_ENDIAN) || defined(__BIG_ENDIAN) || \
            defined(__BIG_ENDIAN__) || defined(__big_endian__) || \
            defined(WORDS_BIGENDIAN)
        #define _CR_ORDER_BE_

    #else
        #define _CR_ORDER_LE_   /* (默认) */
    #endif
#endif  /* !_CR_ORDER_LE_ && !_CR_ORDER_BE_ */

/* 内存模式标识字符串宏 */
#if     defined(_CR_SMALL_)
    #define _CR_MM_STR_ "(tiny)"
#elif   defined(_CR_LARGE_)
    #define _CR_MM_STR_ "(huge)"
#else
    #define _CR_MM_STR_ "(flat)"
#endif

/* 系统位数标识字符串宏 */
#if     defined(_CR_SYS16_)
    #define _CR_SYS_STR_ "{16bit}"
#elif   defined(_CR_SYS32_)
    #define _CR_SYS_STR_ "{32bit}"
#elif   defined(_CR_SYS64_)
    #define _CR_SYS_STR_ "{64bit}"
#endif

/* 字节顺序标识字符串宏 */
#if     defined(_CR_ORDER_LE_)
    #define _CR_ORDER_STR_  "<LE>"
#elif   defined(_CR_ORDER_BE_)
    #define _CR_ORDER_STR_  "<BE>"
#endif

/*****************************************************************************/
/*                               操作系统配置                                */
/*****************************************************************************/

/* Windows CE */
#if     defined(_CR_OS_WINCE_)
    #define _CR_OS_STR_ "@WINCE"

/* Windows 64bit */
#elif   defined(_CR_OS_WIN64_)
    #define _CR_OS_STR_ "@WIN64"

/* Windows 32bit */
#elif   defined(_CR_OS_WIN32_)
    #define _CR_OS_STR_ "@WIN32"

/* DOS under 32bit */
#elif   defined(_CR_OS_DOS32_)
    #define _CR_OS_STR_ "@DOS32"

/* No modern OS */
#elif   defined(_CR_OS_NAKED_)
    #define _CR_OS_STR_ "@NAKED"

/* LINUX */
#elif   defined(_CR_OS_LINUX_)
    #define _CR_OS_STR_ "@LINUX"

/* UNIX */
#elif   defined(_CR_OS_UNIX_)
    #define _CR_OS_STR_ "@UNIX"

#else
    #error "conf.h: OS TYPE not supported yet!"
#endif  /* OS TYPE predefines */

/* 没有 CUI 的选项 */
#if defined(_CR_OS_WINCE_)
    #define _CR_GUI_ONLY_
#endif

/* Windows 头文件精简 */
#if defined(_CR_OS_MSWIN_)
    #undef  WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

/* 文件系统的位数 */
#if defined(_CR_OS_UNIX_) || \
    defined(_CR_OS_WIN32_) || \
    defined(_CR_OS_WIN64_)
    #define _CR_FILE64_
#else
    #define _CR_FILE32_
#endif

/* 内存上限的位数 */
#if defined(_CR_OS_UNIX_) || \
    defined(_CR_OS_WIN32_) || \
    defined(_CR_OS_WIN64_)
    #define _CR_MSIZE64_
#else
    #define _CR_MSIZE32_
#endif

/* 不支持映射文件 */
#if !defined(_CR_OS_UNIX_) && \
    !defined(_CR_OS_WINCE_) && \
    !defined(_CR_OS_WIN32_) && \
    !defined(_CR_OS_WIN64_)
    #define _CR_NO_VPAGE_
#endif

/* API A/W 的开关 */
#if     defined(_CR_OS_WINCE_)
    #define _CR_API_WIDE_ONLY_
#elif   !defined(_CR_OS_MSWIN_)
    #define _CR_API_ANSI_ONLY_
#endif

/* 最大路径的长度 */
#if     defined(_CR_OS_WIN32_) || \
        defined(_CR_OS_WIN64_)
    #define MAX_PATHA   260
    #define MAX_PATHW   32768
#elif   defined(_CR_OS_UNIX_)
    #define MAX_PATHA   4096
    #define MAX_PATHW   4096
#elif   defined(_CR_OS_DOS16_) || \
        defined(_CR_OS_DOS32_) || \
        defined(_CR_OS_WINCE_)
    #define MAX_PATHA   260
    #define MAX_PATHW   260
#endif

/* 文件路径分割符 */
#if     defined(_CR_OS_UNIX_)
    #define CR_SL       "/"
    #define CR_SLASH    '/'     /* UNX 风格 */
#elif   defined(_CR_OS_MACOSH_)
    #define CR_SL       ":"
    #define CR_SLASH    ':'     /* MAC 风格 */
#else
    #define CR_SL       "\\"
    #define CR_SLASH    '\\'    /* DOS 风格 */
#endif

/* 文本的换行字符 */
#if     defined(_CR_OS_UNIX_)
    #define CR_NL   "\n"        /* UNX 风格 */
#elif   defined(_CR_OS_MACOSH_) || \
        defined(_CR_OS_MACOSX_)
    #define CR_NL   "\r"        /* MAC 风格 */
#else
    #define CR_NL   "\r\n"      /* DOS 风格 */
#endif

/* 调试信息的取舍 */
#if defined(_CR_OS_NAKED_)
    #ifndef _CR_ALL_ERROR_INFO_
        #define _CR_NO_ERROR_SET_
    #endif
#endif

/* 异步串口接口开关 */
#if defined(_CR_OS_UNIX_) || \
    defined(_CR_OS_MSWIN_)
    #define _CR_COMMLIB_UART_
#endif

/* 网络 SOCKET 接口开关 */
#if defined(_CR_OS_UNIX_) || \
    defined(_CR_OS_MSWIN_)
    #define _CR_COMMLIB_SOCK_
#endif

/*  网络 SOCKET 不支持 PEEK 操作 */
#if defined(_CR_OS_WINCE_)
    #define _CR_NET_NO_PEEK_
#endif

/*****************************************************************************/
/*                               依赖开关配置                                */
/*****************************************************************************/

/* 字节顺序相关 */
#if defined(_CR_NO_CSWAP_)
    #define _CR_NO_CSWAP32_
    #define _CR_NO_CSWAP64_
#endif
#if defined(_CR_NO_CSWAP32_)
    #define _CR_NO_CSWAP64_
#endif

/* 成员对齐相关 */
#ifndef CR_ALIGN01
    #define CR_ALIGN01  CR_ALIGN(1)
#endif
#ifndef CR_ALIGN02
    #define CR_ALIGN02  CR_ALIGN(2)
#endif
#ifndef CR_ALIGN04
    #define CR_ALIGN04  CR_ALIGN(4)
#endif
#ifndef CR_ALIGN08
    #define CR_ALIGN08  CR_ALIGN(8)
#endif
#ifndef CR_ALIGN16
    #define CR_ALIGN16  CR_ALIGN(16)
#endif

/*****************************************************************************/
/*                               功能开关说明                                */
/*****************************************************************************/

/* 不使用错误信息时的定义
   默认: 使用 */
    /*
#undef  _CR_NO_ERROR_SET_
    */

/* 不使用错误字符串时定义
   默认: 使用 */
    /*
#undef  _CR_NO_ERROR_STR_
    */

/* 打开所有错误信息 (裸机用)
   默认: 不打开 */
    /*
#undef  _CR_ALL_ERROR_INFO_
    */

/* 建立 DLL 时定义 (SO 不用)
   默认: 不建立 DLL */
    /*
#undef  _CR_BUILD_DLL_
    */

/* 文件操作映射到直接系统调用
   默认: 不映射 (可选自己的实现) */
    /*
#undef  _CR_NO_BUF_FILEIO_
    */

/* 使用快速内存长度类型
   默认: 不使用 (只对8位机有效) */
    /*
#undef  _CR_FAST_LENG_
    */

/* 系统中串口的最大个数
   默认: 16 */
#ifndef _CR_SIO_COUNT_
    #define _CR_SIO_COUNT_  16
#endif

/* 长度无关字符串哈希函数常数
   默认: 16 */
#ifndef _CR_HASHSTR_X_
    #define _CR_HASHSTR_X_  16
#endif

/* 缺省哈希表大小常数
   默认: 193 */
#ifndef _CR_DEF_HASH_SIZE_
    #define _CR_DEF_HASH_SIZE_  193
#endif

/* CPU 晶振频率定义
   默认: 11.0592MHz (嵌入式用) */
#ifndef CPU_FOSC
    #define CPU_FOSC    11059200UL
#endif

/* 是否使用 DATA 关键字
   默认: 不使用 (8位机编译器用) */
    /*
#undef  _CR_USE_51_DATA_
    */

/* 是否开启环形队列内联函数
   默认: 不开启 */
    /*
#undef  _CR_USE_BRING_INL_
    */

/* 是否关闭内存释放时的函数指针检查
   默认: 不关闭 (实现跨编译器内存释放)
   关闭后在使用插件的时候会有一些问题
   插件卸掉后释放内存的代码可能也一起卸掉了 */
    /*
#undef  _CR_NO_SAFE_FREE_
    */

/* 是否使用 HeapAlloc 代替 dlmm
   默认: 不代替 (仅限 Windows) */
    /*
#undef  _CR_USE_HEAPALLOC_
    */

/* 是否使用单像素转换函数
   默认: 不使用 (去除静态数据重复) */
    /*
#undef  _CR_USE_PIXELCVT_
    */

/* 屏幕像素使用的格式
   默认: A8R8G8B8/根据目标系统决定 */
#if !defined(_CR_USE_PIXEL15_) && \
    !defined(_CR_USE_PIXEL16_) && \
    !defined(_CR_USE_PIXEL24_) && \
    !defined(_CR_USE_PIXEL32_)
    #if defined(_CR_OS_WINCE_)
        #define _CR_USE_PIXEL16_
    #else
        #define _CR_USE_PIXEL32_
    #endif
#endif

#endif  /* !__CR_CONF_H__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
