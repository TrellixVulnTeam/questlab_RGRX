/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2014-12-02  */
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
/*  >>>>>>>>>>>>>>>>>>>>>>>>> CrHack 高度图函数库 <<<<<<<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_HEIGHTMAP_C__
#define __CR_HEIGHTMAP_C__ 0x0D6C265FUL

#include "safe.h"
#include "memlib.h"
#include "gfx3int.h"

#ifndef _CR_NO_STDC_
    #include <math.h>
#endif

/*
=======================================
    生成高度图
=======================================
*/
CR_API ht_map_t
height_map_new (
  __CR_IN__ const void_t*   data,
  __CR_IN__ uint_t          type,
  __CR_IN__ uint_t          width,
  __CR_IN__ uint_t          height,
  __CR_IN__ fp32_t          grid,
  __CR_IN__ fp32_t          scale
    )
{
    sint_t      tmp;
    leng_t      idx;
    leng_t      size;
    sHEIGHTMAP* rett;

    /* 参数过滤 */
    if (type > HTMAP_TYPE_REAL) {
        err_set(__CR_HEIGHTMAP_C__, type,
                "height_map_new()", "invalid param: type");
        return (NULL);
    }
    if (width < 2) {
        err_set(__CR_HEIGHTMAP_C__, width,
                "height_map_new()", "invalid param: width");
        return (NULL);
    }
    if (height < 2) {
        err_set(__CR_HEIGHTMAP_C__, height,
                "height_map_new()", "invalid param: height");
        return (NULL);
    }
    if (grid <= 0.0f) {
        err_set(__CR_HEIGHTMAP_C__, grid,
                "height_map_new()", "invalid param: grid");
        return (NULL);
    }

    /* 创建对象 */
    rett = struct_new(sHEIGHTMAP);
    if (rett == NULL) {
        err_set(__CR_HEIGHTMAP_C__, CR_NULL,
                "height_map_new()", "struct_new() failure");
        return (NULL);
    }
    if (cut_mul(&size, width, height)) {
        err_set(__CR_HEIGHTMAP_C__, CR_NULL,
                "height_map_new()", "arithmetic mul overflow");
        mem_free(rett);
        return (NULL);
    }
    rett->height = mem_talloc(size, fp32_t);
    if (rett->height == NULL) {
        err_set(__CR_HEIGHTMAP_C__, CR_NULL,
                "height_map_new()", "mem_talloc() failure");
        mem_free(rett);
        return (NULL);
    }
    rett->ww = width;
    rett->hh = height;
    rett->grid = grid;
    rett->inv_grid = 1.0f / grid;

    /* 生成高度图 */
    if (data == NULL) {
        mem_zero(rett->height, size * sizeof(fp32_t));
    }
    else {
        switch (type)
        {
            case HTMAP_TYPE_BYTE:
                for (idx = 0; idx < size; idx++) {
                    tmp = *(byte_t*)data;
                    data = (byte_t*)data + sizeof(byte_t);
                    rett->height[idx] = (fp32_t)tmp;
                    rett->height[idx] *= scale;
                }
                break;

            case HTMAP_TYPE_WORD:
                for (idx = 0; idx < size; idx++) {
                    tmp = *(int16u*)data;
                    data = (byte_t*)data + sizeof(int16u);
                    rett->height[idx] = (fp32_t)tmp;
                    rett->height[idx] *= scale;
                }
                break;

            case HTMAP_TYPE_SINT:
                for (idx = 0; idx < size; idx++) {
                    tmp = *(sint_t*)data;
                    data = (byte_t*)data + sizeof(sint_t);
                    rett->height[idx] = (fp32_t)tmp;
                    rett->height[idx] *= scale;
                }
                break;

            default:
            case HTMAP_TYPE_REAL:
                mem_cpy(rett->height, data, size * sizeof(fp32_t));
                break;
        }
    }
    return ((ht_map_t)rett);
}

/*
=======================================
    释放高度图
=======================================
*/
CR_API void_t
height_map_del (
  __CR_IN__ ht_map_t    htmap
    )
{
    sHEIGHTMAP* real;

    real = (sHEIGHTMAP*)htmap;
    mem_free(real->height);
    mem_free(htmap);
}

/*
=======================================
    获取高度值
=======================================
*/
CR_API fp32_t
height_map_get (
  __CR_IN__ ht_map_t    htmap,
  __CR_IN__ fp32_t      x,
  __CR_IN__ fp32_t      z
    )
{
    sint_t  uu, vv;
    fp32_t  t1, t2, t3;
    fp32_t  h1, h2, h3, *height;
    /* ---------------------- */
    sHEIGHTMAP* real = (sHEIGHTMAP*)htmap;

    x *= real->inv_grid;
    z *= real->inv_grid;
    uu = (sint_t)x;
    vv = (sint_t)z;
    if (uu < 0)
        uu = 0;
    else
    if (uu >= (sint_t)(real->ww - 1))
        uu = real->ww - 2;
    if (vv < 0)
        vv = 0;
    else
    if (vv >= (sint_t)(real->hh - 1))
        vv = real->hh - 2;
    height = &real->height[vv * real->ww + uu];

    h1 = height[0];
    h2 = height[1] - h1;
    h3 = height[real->ww + 1] - h2 - h1;

    t1 = x - uu;
    t2 = z - vv;
    t3 = t1 - t2;
    if (t3 > 0.0f)
        return (t1 * h2 + t2 * h3 + h1);
    h2 = height[real->ww + 0] - h1;
    h3 = height[real->ww + 1] - h2 - h1;
    return (t1 * h3 + t2 * h2 + h1);
}

/*
=======================================
    获取顶点法线
=======================================
*/
CR_API void_t
height_map_nrm (
  __CR_IN__ ht_map_t    htmap,
  __CR_OT__ vec3d_t*    normal,
  __CR_IN__ uint_t      x,
  __CR_IN__ uint_t      z,
  __CR_IN__ bool_t      is_nrm
    )
{
    fp32_t  length;
    sint_t  delta1 = -1, delta2 = 1;
    sint_t  delta3 = -1, delta4 = 1;
    /* -------------------------- */
    sHEIGHTMAP* real = (sHEIGHTMAP*)htmap;

    if (x == 0) {
        delta1 = 0;
    }
    else
    if (x >= real->ww - 1) {
        x = real->ww - 1;
        delta2 = 0;
    }
    if (z == 0) {
        delta3 = 0;
    }
    else
    if (z >= real->hh - 1) {
        z = real->hh - 1;
        delta4 = 0;
    }
    normal->x = real->height[z * real->ww + x + delta1] -
                real->height[z * real->ww + x + delta2];
    normal->y = 2.0f * real->grid;
    normal->z = real->height[(z + delta4) * real->ww + x] -
                real->height[(z + delta3) * real->ww + x];
    if (is_nrm) {
        length = FSQRT(normal->x * normal->x +
                       normal->y * normal->y +
                       normal->z * normal->z);
        normal->x /= length;
        normal->y /= length;
        normal->z /= length;
    }
}

/*
=======================================
    获取块包围盒
=======================================
*/
CR_API void_t
height_map_aabb (
  __CR_IN__ ht_map_t    htmap,
  __CR_OT__ sAABB*      aabb,
  __CR_IN__ uint_t      x,
  __CR_IN__ uint_t      z,
  __CR_IN__ uint_t      w,
  __CR_IN__ uint_t      h
    )
{
    fp32_t  tmp;
    uint_t  ii, jj;
    vec3d_t box[2];
    /* --------- */
    sHEIGHTMAP* real;

    real = (sHEIGHTMAP*)htmap;
    if (x >= real->ww - 1)
        x = real->ww - 2;
    if (z >= real->hh - 1)
        z = real->hh - 2;
    if (w > real->ww - x)
        w = real->ww - x;
    if (h > real->hh - z)
        h = real->hh - z;

    box[0].x = x * real->grid;
    box[0].y = real->height[z * real->ww + x];
    box[0].z = z * real->grid;
    box[1].x = (x + w - 1) * real->grid;
    box[1].y = box[0].y;
    box[1].z = (z + h - 1) * real->grid;

    for (ii = z; ii < z + h; ii++)
    for (jj = x; jj < x + w; jj++) {
        tmp = real->height[ii * real->ww + jj];
        if (tmp < box[0].y)
            box[0].y = tmp;
        if (tmp > box[1].y)
            box[1].y = tmp;
    }
    bound_get_aabb(aabb, box, 2, sizeof(vec3d_t));
}

/*
=======================================
    放置包围盒
=======================================
*/
CR_API fp32_t
height_map_place (
  __CR_IN__ ht_map_t        htmap,
  __CR_IN__ const sAABB*    aabb,
  __CR_IN__ fp32_t          x,
  __CR_IN__ fp32_t          z,
  __CR_IN__ bool_t          large
    )
{
    uint_t  idx;
    fp32_t  min, tmp;

    if (large)
    {
        /* 四个边框的最小高度 */
        min = height_map_get(htmap, aabb->v[0].x + x,
                                    aabb->v[0].z + z);
        for (idx = 1; idx < 4; idx++) {
            tmp = height_map_get(htmap, aabb->v[idx].x + x,
                                        aabb->v[idx].z + z);
            if (min > tmp)
                min = tmp;
        }
    }
    else
    {
        /* 以物体中心点取高度 */
        min = height_map_get(htmap, x, z);
    }

    /* 计算底面的偏移值 */
    return (min - aabb->v[4].y);
}

#endif  /* !__CR_HEIGHTMAP_C__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
