/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2013-06-05  */
/*     #######          ###    ###      [GFX3]      ###  ~~~~~~~~~~~~~~~~~~  */
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
/*  >>>>>>>>>>>>>>>>>>>>>>>> CrHack 三维图形头文件 <<<<<<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_GFX3_H__
#define __CR_GFX3_H__ 0x190ECB8EUL

#include "gfx2.h"

/*****************************************************************************/
/*                                 数据结构                                  */
/*****************************************************************************/

/* 二维向量 */
typedef struct
{
        fp32_t  x, y;

} vec2d_t;

/* 三维向量 */
typedef struct
{
        fp32_t  x, y, z;

} vec3d_t;

/* 四维向量 */
typedef struct
{
        fp32_t  x, y, z, w;

} vec4d_t, sPLANE, sQUATO;

/*
********************
    D3D 行主矩阵
    OGL 列主矩阵
********************
*/

/* 3x3 矩阵 */
typedef struct
{
        fp32_t  m[3 * 3];

} mat3x3_t;

/* 4x4 矩阵 */
typedef struct
{
        fp32_t  m[4 * 4];

} mat4x4_t;

/* 射线 */
typedef struct
{
        vec3d_t     pos;
        vec3d_t     dir;

} sRADIAL;

/* 四边形 (left-top, cw) */
typedef struct
{
        vec3d_t     v[4];
} sQUAD;

/* AABB 包围盒 (left-top-up, cw) */
typedef struct
{
        vec3d_t     v[8];
} sAABB;

/* 包围球 */
typedef struct
{
        vec3d_t     center;
        fp32_t      radius;

} sSPHERE;

/* 视锥 (near, far, left, right, top, bottom) */
typedef struct
{
        sPLANE  p[6];

} sFRUSTUM;

/* 只使用微软自家的编译器 */
#if     defined(_CR_CC_MSC_) && (_CR_CC_VER_ >= 1400)
/*****************************************************************************/
/*                              Direct3D8 API                                */
/*****************************************************************************/
#if     defined(_CR_USE_D3D8_) && (_CR_CC_VER_ < 1700)

#include "gfx3/d3d8api.h"
#include "gfx3/d3d8api.inl"

/*****************************************************************************/
/*                              Direct3D9 API                                */
/*****************************************************************************/
#elif   defined(_CR_USE_D3D9_) && (_CR_CC_VER_ < 1700)

#include "gfx3/d3d9api.h"
#include "gfx3/d3d9api.inl"

/*****************************************************************************/
/*                              Direct3D11 API                               */
/*****************************************************************************/
#elif   defined(_CR_USE_D3D11_)

#include "gfx3/d3d11api.h"
#include "gfx3/d3d11api.inl"

#endif  /* GFX3 API predefines */

#endif  /* _CR_CC_MSC_ && _CR_CC_VER_ */

#endif  /* !__CR_GFX3_H__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
