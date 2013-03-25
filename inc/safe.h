/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2009-12-16  */
/*     #######          ###    ###      [CORE]      ###  ~~~~~~~~~~~~~~~~~~  */
/*    ########          ###    ###                  ###  MODIFY: 2013-03-25  */
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
/*  >>>>>>>>>>>>>>>>>>>>>>>> CrHack 数值安全头文件 <<<<<<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_SAFE_H__
#define __CR_SAFE_H__ 0x6B16BC55UL

#include "defs.h"

/*
=======================================
    平台整数截断检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_size (
  __CR_OT__ uint_t* dst,
  __CR_IN__ leng_t  val
    )
{
    uint_t  tmp = (uint_t)val;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp == val) ? FALSE : TRUE);
}

/*
=======================================
    平台整数截断检查 (有符号)
=======================================
*/
safe_inline bool_t
cut_dist (
  __CR_OT__ sint_t* dst,
  __CR_IN__ dist_t  val
    )
{
    sint_t  tmp = (sint_t)val;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp == val) ? FALSE : TRUE);
}

/*
=======================================
    32位整数截断检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_int32u (
  __CR_OT__ leng_t* dst,
  __CR_IN__ int32u  val
    )
{
    leng_t  tmp = (leng_t)val;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp == val) ? FALSE : TRUE);
}

/*
=======================================
    32位整数截断检查 (有符号)
=======================================
*/
safe_inline bool_t
cut_int32s (
  __CR_OT__ dist_t* dst,
  __CR_IN__ int32s  val
    )
{
    dist_t  tmp = (dist_t)val;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp == val) ? FALSE : TRUE);
}

/*
=======================================
    64位整数截断检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_int64u (
  __CR_OT__ leng_t* dst,
  __CR_IN__ int64u  val
    )
{
#ifndef _CR_NO_INT64_
    leng_t  tmp = (leng_t)val;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp == val) ? FALSE : TRUE);
#else
    leng_t  tmp = (leng_t)val.lo32;

    if (dst != NULL)
       *dst  = tmp;
    return ((val.lo32 == tmp &&
             val.hi32 == 0L) ? FALSE : TRUE);
#endif
}

/*
=======================================
    64位整数截断检查 (有符号)
=======================================
*/
safe_inline bool_t
cut_int64s (
  __CR_OT__ dist_t* dst,
  __CR_IN__ int64s  val
    )
{
#ifndef _CR_NO_INT64_
    dist_t  tmp = (dist_t)val;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp == val) ? FALSE : TRUE);
#else
    dist_t  tmp = (dist_t)val.lo32;

    if (dst != NULL)
       *dst  = tmp;

    if (val.lo32 == tmp) {
        if (val.hi32 ==  0L)
            return (FALSE);
        if (val.hi32 == -1L && tmp < 0)
            return (FALSE);
    }
    return (TRUE);
#endif
}

/*
=======================================
    32-整数截断检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_int32_u (
  __CR_OT__ uint_t* dst,
  __CR_IN__ int32u  val
    )
{
    uint_t  tmp = (uint_t)val;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp == val) ? FALSE : TRUE);
}

/*
=======================================
    32-整数截断检查 (有符号)
=======================================
*/
safe_inline bool_t
cut_int32_s (
  __CR_OT__ sint_t* dst,
  __CR_IN__ int32s  val
    )
{
    sint_t  tmp = (sint_t)val;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp == val) ? FALSE : TRUE);
}

/*
=======================================
    64-32位整数截断检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_int64_32u (
  __CR_OT__ int32u* dst,
  __CR_IN__ int64u  val
    )
{
#ifndef _CR_NO_INT64_
    int32u  tmp = (int32u)val;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp == val) ? FALSE : TRUE);
#else
    int32u  tmp = (int32u)val.lo32;

    if (dst != NULL)
       *dst  = tmp;
    return ((val.lo32 == tmp &&
             val.hi32 == 0L) ? FALSE : TRUE);
#endif
}

/*
=======================================
    64-32位整数截断检查 (有符号)
=======================================
*/
safe_inline bool_t
cut_int64_32s (
  __CR_OT__ int32s* dst,
  __CR_IN__ int64s  val
    )
{
#ifndef _CR_NO_INT64_
    int32s  tmp = (int32s)val;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp == val) ? FALSE : TRUE);
#else
    int32s  tmp = (int32s)val.lo32;

    if (dst != NULL)
       *dst  = tmp;

    if (val.lo32 == tmp) {
        if (val.hi32 ==  0L)
            return (FALSE);
        if (val.hi32 == -1L && tmp < 0)
            return (FALSE);
    }
    return (TRUE);
#endif
}

/*
=======================================
    平台加法溢出检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_addu (
  __CR_OT__ leng_t* dst,
  __CR_IN__ leng_t  val1,
  __CR_IN__ leng_t  val2
    )
{
    leng_t  tmp = val1 + val2;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp >= val1) ? FALSE : TRUE);
}

/*
=======================================
    平台加法溢出检查 (有符号)
=======================================
*/
safe_inline bool_t
cut_adds (
  __CR_OT__ dist_t* dst,
  __CR_IN__ dist_t  val1,
  __CR_IN__ dist_t  val2
    )
{
    dist_t  tmp = val1 + val2;

    if (dst != NULL)
       *dst  = tmp;
    return (((tmp ^ val1) >= 0 ||
             (tmp ^ val2) >= 0) ? FALSE : TRUE);
}

/*
=======================================
    整数加法溢出检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_add_u (
  __CR_OT__ uint_t* dst,
  __CR_IN__ uint_t  val1,
  __CR_IN__ uint_t  val2
    )
{
    uint_t  tmp = val1 + val2;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp >= val1) ? FALSE : TRUE);
}

/*
=======================================
    字节加法溢出检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_add08 (
  __CR_OT__ byte_t* dst,
  __CR_IN__ byte_t  val1,
  __CR_IN__ byte_t  val2
    )
{
    byte_t  tmp = val1 + val2;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp >= val1) ? FALSE : TRUE);
}

/*
=======================================
    单字加法溢出检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_add16 (
  __CR_OT__ int16u* dst,
  __CR_IN__ int16u  val1,
  __CR_IN__ int16u  val2
    )
{
    int16u  tmp = val1 + val2;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp >= val1) ? FALSE : TRUE);
}

/*
=======================================
    双字加法溢出检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_add32 (
  __CR_OT__ int32u* dst,
  __CR_IN__ int32u  val1,
  __CR_IN__ int32u  val2
    )
{
    int32u  tmp = val1 + val2;

    if (dst != NULL)
       *dst  = tmp;
    return ((tmp >= val1) ? FALSE : TRUE);
}

/*
=======================================
    文件偏移加法溢出检查
=======================================
*/
safe_inline bool_t
cut_addfs (
  __CR_OT__ fdist_t*    dst,
  __CR_IN__ fdist_t     val1,
  __CR_IN__ fdist_t     val2
    )
{
    fdist_t tmp = val1 + val2;

    if (dst != NULL)
       *dst  = tmp;
    return (((tmp ^ val1) >= 0 ||
             (tmp ^ val2) >= 0) ? FALSE : TRUE);
}

/*
=======================================
    平台乘法溢出检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_mul (
  __CR_OT__ leng_t* dst,
  __CR_IN__ leng_t  val1,
  __CR_IN__ leng_t  val2
    )
{
    leng_t  tmp = val1 * val2;

    if (dst != NULL)
       *dst  = tmp;
    if (val1 <= 1 || val2 <= 1)
        return (FALSE);
    return ((tmp / val2 == val1) ? FALSE : TRUE);
}

/*
=======================================
    平台乘加溢出检查 (无符号)
=======================================
*/
safe_inline bool_t
cut_mad (
  __CR_OT__ leng_t* dst,
  __CR_IN__ leng_t  mul1,
  __CR_IN__ leng_t  mul2,
  __CR_IN__ leng_t  add
    )
{
    leng_t  tmp;

    if (cut_mul(&tmp, mul1, mul2))
        return (TRUE);
    return (cut_addu(dst, tmp, add));
}

/*
=======================================
    模型大小安全检查
=======================================
*/
safe_inline bool_t
cut_model (
  __CR_OT__ leng_t* size,
  __CR_IN__ uint_t  count,
  __CR_IN__ leng_t  bpu
    )
{
    if (count == 0 || bpu == 0)
        return (TRUE);
    return (cut_mul(size, count, bpu));
}

/*
=======================================
    图片宽高安全检查
=======================================
*/
safe_inline bool_t
cut_image (
  __CR_OT__ leng_t* size,
  __CR_IN__ uint_t  width,
  __CR_IN__ uint_t  height,
  __CR_IN__ leng_t  bpc
    )
{
    leng_t  tmp;

    if (width == 0 || height == 0)
        return (TRUE);
    if (cut_mul(&tmp, width, height))
        return (TRUE);

    /* 保守到 DXT5 计算 */
    if (bpc <= 1) {
        if (size != NULL)
           *size  = tmp;
        return (FALSE);
    }
    return (cut_mul(size, tmp, bpc));
}

#endif  /* !__CR_SAFE_H__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
