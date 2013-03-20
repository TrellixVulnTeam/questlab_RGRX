/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2010-01-27  */
/*     #######          ###    ###      [BLIT]      ###  ~~~~~~~~~~~~~~~~~~  */
/*    ########          ###    ###                  ###  MODIFY: 2012-08-01  */
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
/*  >>>>>>>>>>>>>>>>>>>>>>> CRHACK/BLIT 主程序入口点 <<<<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_BLIT_C__
#define __CR_BLIT_C__ 0x1A530F26UL

#include "blit.h"
#include "memlib.h"
#include "pixels.h"
#include "strlib.h"

/* DLL 自定义入口点 */
#ifdef  _CR_BUILD_DLL_

#include <windows.h>

/*
=======================================
    CRHACK/BLIT DLL 入口点
=======================================
*/
#if defined(_CR_CC_BCC_)
int  WINAPI
DllEntryPoint (
  __CR_IN__ HINSTANCE       hinst,
  __CR_IN__ unsigned long   reason,
  __CR_UU__ void*           reserved
    )
#else
BOOL WINAPI
DllMain (
  __CR_IN__ HANDLE  hinst,
  __CR_IN__ DWORD   reason,
  __CR_UU__ LPVOID  reserved
    )
#endif
{
    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            break;

        case DLL_PROCESS_DETACH:
            break;
    }
    CR_NOUSE(hinst);
    CR_NOUSE(reserved);
    return (TRUE);
}

#endif  /* _CR_BUILD_DLL_ */

/*****************************************************************************/
/*                                 绘制接口                                  */
/*****************************************************************************/

/*
---------------------------------------
    释放图形绘制接口
---------------------------------------
*/
static void_t
iGFX2_MEM_release (
  __CR_IN__ iGFX2*  that
    )
{
    mem_free(that->__back__.data);
    mem_free(that);
}

/*
---------------------------------------
    获取扩展的绘制接口
---------------------------------------
*/
static void_t*
iGFX2_MEM_getMore (
  __CR_IN__ iGFX2*  that,
  __CR_IN__ port_t  iid
    )
{
    /* 判断一下名称 */
    if (str_cmpA(iid, "iGFX2::MEM") != 0)
        return (NULL);
    return ((void_t*)that);
}

/*
---------------------------------------
    改变屏幕大小
---------------------------------------
*/
static bool_t
iGFX2_MEM_reset (
  __CR_IN__ iGFX2*  that
    )
{
    CR_NOUSE(that);
    return (FALSE);
}

/*
---------------------------------------
    锁住后台缓冲
---------------------------------------
*/
static sIMAGE*
iGFX2_MEM_lock (
  __CR_IN__ iGFX2*  that
    )
{
    return (&that->__back__);
}

/*
---------------------------------------
    解锁后台缓冲
---------------------------------------
*/
static void_t
iGFX2_MEM_unlock (
  __CR_IN__ iGFX2*  that
    )
{
    CR_NOUSE(that);
}

/*
---------------------------------------
    显示后台缓冲
---------------------------------------
*/
static bool_t
iGFX2_MEM_flip (
  __CR_IN__ iGFX2*  that,
  __CR_IN__ bool_t  sync
    )
{
    CR_NOUSE(that);
    CR_NOUSE(sync);
    return (FALSE);
}

/*
---------------------------------------
    清除后台缓冲
---------------------------------------
*/
#define _image_clear01  iGFX2_MEM_clear01
#define _image_clear04  iGFX2_MEM_clear04
#define _image_clear08  iGFX2_MEM_clear08
#define _image_clear12  iGFX2_MEM_clear12
#define _image_clear15  iGFX2_MEM_clear15
#define _image_clear16  iGFX2_MEM_clear16
#define _image_clear17  iGFX2_MEM_clear17
#define _image_clear24  iGFX2_MEM_clear24
#define _image_clear32  iGFX2_MEM_clear32

#include "../templ/clear2d.inl"

/*
---------------------------------------
    设置后台调色板
---------------------------------------
*/
static bool_t
iGFX2_MEM_setPal (
  __CR_IN__ iGFX2*  that,
  __CR_IN__ uint_t  start,
  __CR_IN__ uint_t  count
    )
{
    CR_NOUSE(that);
    CR_NOUSE(start);
    CR_NOUSE(count);
    return (FALSE);
}

/* 接口虚函数表 */
static const iGFX2_vtbl _rom_ s_bmp01_vtbl =
{
    iGFX2_MEM_release, iGFX2_MEM_getMore,
    iGFX2_MEM_reset, iGFX2_MEM_lock, iGFX2_MEM_unlock,
    iGFX2_MEM_flip, iGFX2_MEM_clear01, iGFX2_MEM_setPal,
};

static const iGFX2_vtbl _rom_ s_bmp04_vtbl =
{
    iGFX2_MEM_release, iGFX2_MEM_getMore,
    iGFX2_MEM_reset, iGFX2_MEM_lock, iGFX2_MEM_unlock,
    iGFX2_MEM_flip, iGFX2_MEM_clear04, iGFX2_MEM_setPal,
};

static const iGFX2_vtbl _rom_ s_bmp08_vtbl =
{
    iGFX2_MEM_release, iGFX2_MEM_getMore,
    iGFX2_MEM_reset, iGFX2_MEM_lock, iGFX2_MEM_unlock,
    iGFX2_MEM_flip, iGFX2_MEM_clear08, iGFX2_MEM_setPal,
};

static const iGFX2_vtbl _rom_ s_bmp12_vtbl =
{
    iGFX2_MEM_release, iGFX2_MEM_getMore,
    iGFX2_MEM_reset, iGFX2_MEM_lock, iGFX2_MEM_unlock,
    iGFX2_MEM_flip, iGFX2_MEM_clear12, iGFX2_MEM_setPal,
};

static const iGFX2_vtbl _rom_ s_bmp15_vtbl =
{
    iGFX2_MEM_release, iGFX2_MEM_getMore,
    iGFX2_MEM_reset, iGFX2_MEM_lock, iGFX2_MEM_unlock,
    iGFX2_MEM_flip, iGFX2_MEM_clear15, iGFX2_MEM_setPal,
};

static const iGFX2_vtbl _rom_ s_bmp16_vtbl =
{
    iGFX2_MEM_release, iGFX2_MEM_getMore,
    iGFX2_MEM_reset, iGFX2_MEM_lock, iGFX2_MEM_unlock,
    iGFX2_MEM_flip, iGFX2_MEM_clear16, iGFX2_MEM_setPal,
};

static const iGFX2_vtbl _rom_ s_bmp17_vtbl =
{
    iGFX2_MEM_release, iGFX2_MEM_getMore,
    iGFX2_MEM_reset, iGFX2_MEM_lock, iGFX2_MEM_unlock,
    iGFX2_MEM_flip, iGFX2_MEM_clear17, iGFX2_MEM_setPal,
};

static const iGFX2_vtbl _rom_ s_bmp24_vtbl =
{
    iGFX2_MEM_release, iGFX2_MEM_getMore,
    iGFX2_MEM_reset, iGFX2_MEM_lock, iGFX2_MEM_unlock,
    iGFX2_MEM_flip, iGFX2_MEM_clear24, iGFX2_MEM_setPal,
};

static const iGFX2_vtbl _rom_ s_bmp32_vtbl =
{
    iGFX2_MEM_release, iGFX2_MEM_getMore,
    iGFX2_MEM_reset, iGFX2_MEM_lock, iGFX2_MEM_unlock,
    iGFX2_MEM_flip, iGFX2_MEM_clear32, iGFX2_MEM_setPal,
};

/*
=======================================
    生成 MEM 图形离屏表面
=======================================
*/
CR_API iGFX2*
create_mem_bitmap (
  __CR_IN__ uint_t          width,
  __CR_IN__ uint_t          height,
  __CR_IN__ uint_t          crh_fmt,
  __CR_IN__ int32u          ext_fmt,
  __CR_IN__ const int32u*   param,
  __CR_IN__ uint_t          count
    )
{
    iGFX2*  gfx2;
    sIMAGE* image;

    CR_NOUSE(param);
    CR_NOUSE(count);
    CR_NOUSE(ext_fmt);

    gfx2 = struct_new(iGFX2);
    if (gfx2 == NULL) {
        err_set(__CR_BLIT_C__, CR_NULL,
                "create_mem_bitmap()", "struct_new() failure");
        return (NULL);
    }

    /* 仅支持 CrHack 的部分类型 */
    switch (crh_fmt)
    {
        case CR_INDEX1:   gfx2->__vptr__ = &s_bmp01_vtbl; break;
        case CR_INDEX4:   gfx2->__vptr__ = &s_bmp04_vtbl; break;
        case CR_INDEX8:   gfx2->__vptr__ = &s_bmp08_vtbl; break;
        case CR_ARGB4444: gfx2->__vptr__ = &s_bmp12_vtbl; break;
        case CR_ARGBX555: gfx2->__vptr__ = &s_bmp15_vtbl; break;
        case CR_ARGB565:  gfx2->__vptr__ = &s_bmp16_vtbl; break;
        case CR_ARGB1555: gfx2->__vptr__ = &s_bmp17_vtbl; break;
        case CR_ARGB888:  gfx2->__vptr__ = &s_bmp24_vtbl; break;
        case CR_ARGB8888: gfx2->__vptr__ = &s_bmp32_vtbl; break;

        default:
            err_set(__CR_BLIT_C__, crh_fmt,
                    "create_mem_bitmap()", "invalid param: crh_fmt");
            goto _failure;
    }

    /* 使用行8字节对齐 ----------- VV (多分配一行) */
    image = image_new(0, 0, width, height + 1, crh_fmt, FALSE, 8);
    if (image == NULL) {
        err_set(__CR_BLIT_C__, CR_NULL,
                "create_mem_bitmap()", "image_new() failure");
        goto _failure;
    }
    /* 设置正确的参数 */
    image->clip_win.y2--;
    image->clip_win.hh--;
    image->position.y2--;
    image->position.hh--;
    image->size -= image->bpl;

    /* 复制过去后释放结构 */
    struct_cpy(&gfx2->__back__, image, sIMAGE);
    mem_free(image);
    return ((iGFX2*)gfx2);

_failure:
    mem_free(gfx2);
    return (NULL);
}

#endif  /* !__CR_BLIT_C__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
