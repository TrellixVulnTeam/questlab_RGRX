
#include "../QstLibs/QstLibs.h"

#include <math.h>

/*
---------------------------------------
    图片逻辑-与
---------------------------------------
*/
static bool_t
fill_and_x86 (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    sFILL   fill;
    cpix_t  clrs;
    sIMAGE* dest;

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    fill.dx = fill.dy = 0;
    fill.dw = dest->position.ww;
    fill.dh = dest->position.hh;
    clrs.val = xml_attr_intx32U("mask", 0xFFFFFFFF, param);
    fill_and32_c(dest, &fill, clrs, NULL);
    return (TRUE);
}

/*
---------------------------------------
    图片逻辑-或
---------------------------------------
*/
static bool_t
fill_orr_x86 (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    sFILL   fill;
    cpix_t  clrs;
    sIMAGE* dest;

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    fill.dx = fill.dy = 0;
    fill.dw = dest->position.ww;
    fill.dh = dest->position.hh;
    clrs.val = xml_attr_intx32U("mask", 0x00000000, param);
    fill_orr32_c(dest, &fill, clrs, NULL);
    return (TRUE);
}

/*
---------------------------------------
    图片逻辑-非
---------------------------------------
*/
static bool_t
fill_not_x86 (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    sFILL   fill;
    cpix_t  clrs;
    sIMAGE* dest;

    CR_NOUSE(param);
    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    fill.dx = fill.dy = 0;
    fill.dw = dest->position.ww;
    fill.dh = dest->position.hh;
    clrs.val = 0x00000000;
    fill_not32_c(dest, &fill, clrs, NULL);
    return (TRUE);
}

/*
---------------------------------------
    图片逻辑异或
---------------------------------------
*/
static bool_t
fill_xor_x86 (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    sFILL   fill;
    cpix_t  clrs;
    sIMAGE* dest;

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    fill.dx = fill.dy = 0;
    fill.dw = dest->position.ww;
    fill.dh = dest->position.hh;
    clrs.val = xml_attr_intx32U("mask", 0x00000000, param);
    fill_xor32_c(dest, &fill, clrs, NULL);
    return (TRUE);
}

/*
---------------------------------------
    图片饱和加法
---------------------------------------
*/
static bool_t
fill_add_x86 (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    sFILL   fill;
    cpix_t  clrs;
    sIMAGE* dest;

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    fill.dx = fill.dy = 0;
    fill.dw = dest->position.ww;
    fill.dh = dest->position.hh;
    clrs.val = xml_attr_intx32U("color", 0x00000000, param);
    fill_add32_c(dest, &fill, clrs, NULL);
    return (TRUE);
}

/*
---------------------------------------
    图片饱和减法
---------------------------------------
*/
static bool_t
fill_sub_x86 (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    sFILL   fill;
    cpix_t  clrs;
    sIMAGE* dest;

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    fill.dx = fill.dy = 0;
    fill.dw = dest->position.ww;
    fill.dh = dest->position.hh;
    clrs.val = xml_attr_intx32U("color", 0x00000000, param);
    fill_sub32_c(dest, &fill, clrs, NULL);
    return (TRUE);
}

/*
---------------------------------------
    图片插值填充
---------------------------------------
*/
static bool_t
fill_lrp_x86 (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    sFILL   fill;
    cpix_t  clrs;
    sIMAGE* dest;

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    fill.dx = fill.dy = 0;
    fill.dw = dest->position.ww;
    fill.dh = dest->position.hh;
    clrs.val = xml_attr_intx32U("color", 0x00000000, param);
    fill_lrp32_c(dest, &fill, clrs, NULL);
    return (TRUE);
}

/*
---------------------------------------
    图片垂直翻转
---------------------------------------
*/
static bool_t
flip_vertical (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    CR_NOUSE(nouse);
    CR_NOUSE(param);
    image_flp((sIMAGE*)image, FALSE);
    return (TRUE);
}

/*
---------------------------------------
    图片 RB 互换
---------------------------------------
*/
static bool_t
swap_red_blue (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    leng_t  size;
    byte_t* data;
    sIMAGE* dest;

    CR_NOUSE(nouse);
    CR_NOUSE(param);
    dest = (sIMAGE*)image;
    if (dest->fmt == CR_ARGB8888) {
        size = dest->size;
        data = dest->data;
        for (size /= 4; size != 0; size--) {
            swap_rb32(data);
            data += sizeof(int32u);
        }
    }
    return (TRUE);
}

/* 颜色扩散细分 */
#define DIFFUSE_MAX     256

/*
---------------------------------------
    图片颜色扩散
---------------------------------------
*/
static bool_t
image_diffuse (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    int32u* pos1;
    int32u* pos2;
    sIMAGE* dest;
    sint_t  minx, miny;
    sint_t  maxx, maxy;
    sint_t  dx, dy, ww, hh;

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    if (dest->fmt != CR_ARGB8888)
        return (TRUE);
    minx = (sint_t)xml_attr_intxU("min_x", (uint_t)-5, param);
    maxx = (sint_t)xml_attr_intxU("max_x", (uint_t)+5, param);
    miny = (sint_t)xml_attr_intxU("min_y", (uint_t)-5, param);
    maxy = (sint_t)xml_attr_intxU("max_y", (uint_t)+5, param);
    maxx -= minx;
    maxy -= miny;
    rand_seed(timer_get32());
    ww = (sint_t)dest->position.ww;
    hh = (sint_t)dest->position.hh;
    for (sint_t yy = 0; yy < hh; yy++)
    for (sint_t xx = 0; xx < ww; xx++)
    {
        dx = rand_getx(DIFFUSE_MAX);
        dy = rand_getx(DIFFUSE_MAX);
        dx = (dx * maxx) / DIFFUSE_MAX + minx;
        dy = (dy * maxy) / DIFFUSE_MAX + miny;
        pos1 = pixel_addr4(dest, xx, yy);
        if (xx + dx < 0 || xx + dx >= ww)
            dx = 0;
        if (yy + dy < 0 || yy + dy >= hh)
            dy = 0;
        pos2 = pixel_addr4(dest, xx + dx, yy + dy);
        pos2[0] = pos1[0];
    }
    return (TRUE);
}

/*
---------------------------------------
    图片灰度转换
---------------------------------------
*/
static bool_t
image_graying (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    byte_t* ptr;
    byte_t* line;
    sIMAGE* dest;
    uint_t  ww, hh, ii;

    CR_NOUSE(nouse);
    CR_NOUSE(param);
    dest = (sIMAGE*)image;
    if (dest->fmt != CR_ARGB8888)
        return (TRUE);
    line = dest->data;
    ww = dest->position.ww;
    hh = dest->position.hh;
    for (uint_t yy = 0; yy < hh; yy++) {
        ptr = line;
        for (uint_t xx = 0; xx < ww; xx++) {
            ii = rgb2light(ptr[2], ptr[1], ptr[0]);
            ptr[0] = (byte_t)ii;
            ptr[1] = (byte_t)ii;
            ptr[2] = (byte_t)ii;
            ptr += sizeof(int32u);
        }
        line += dest->bpl;
    }
    return (TRUE);
}

/*
---------------------------------------
    图片二值转换
---------------------------------------
*/
static bool_t
image_binaryz (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    byte_t* ptr;
    byte_t* line;
    sIMAGE* dest;
    uint_t  gate;
    uint_t  ww, hh;

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    if (dest->fmt != CR_ARGB8888)
        return (TRUE);
    line = dest->data;
    ww = dest->position.ww;
    hh = dest->position.hh;
    gate = xml_attr_intxU("gate", 127, param);
    if (param->found)
    {
        /* 有参数使用指定参数 */
        for (uint_t yy = 0; yy < hh; yy++) {
            ptr = line;
            for (uint_t xx = 0; xx < ww; xx++) {
                if (ptr[0] > gate)
                    ptr[0] = 0xFF;
                else
                    ptr[0] = 0x00;
                ptr[1] = ptr[0];
                ptr[2] = ptr[0];
                ptr += sizeof(int32u);
            }
            line += dest->bpl;
        }
    }
    else
    {
        int64u  total = 0;

        /* 没有参数使用平均值 */
        for (uint_t yy = 0; yy < hh; yy++) {
            ptr = line;
            for (uint_t xx = 0; xx < ww; xx++) {
                total += ptr[0];
                ptr += sizeof(int32u);
            }
            line += dest->bpl;
        }
        total /= ww;
        total /= hh;
        gate = (uint_t)total;
        line = dest->data;
        for (uint_t yy = 0; yy < hh; yy++) {
            ptr = line;
            for (uint_t xx = 0; xx < ww; xx++) {
                if (ptr[0] > gate)
                    ptr[0] = 0xFF;
                else
                    ptr[0] = 0x00;
                ptr[1] = ptr[0];
                ptr[2] = ptr[0];
                ptr += sizeof(int32u);
            }
            line += dest->bpl;
        }
    }
    return (TRUE);
}

/*
---------------------------------------
    卷积运算 (3 x 3)
---------------------------------------
*/
static byte_t*
conv3x3_main (
  __CR_IN__ const sIMAGE*   src,
  __CR_IN__ const sint_t    mat[9]
    )
{
    byte_t* ptr;
    byte_t* dst;
    byte_t* prev;
    byte_t* curt;
    byte_t* next;
    sint_t  csum;
    uint_t  xx, yy;
    uint_t  ww, hh;

    /* 不处理边框 */
    ww = src->position.ww;
    hh = src->position.hh;
    if (ww < 3 || hh < 3)
        return (NULL);
    ww -= 2;
    hh -= 2;
    dst = (byte_t*)mem_malloc(ww * hh * 4);
    if (dst == NULL)
        return (NULL);
    ptr = dst;

    /* 求矩阵的和 */
    for (csum = mat[0], xx = 1; xx < 9; xx++)
        csum += mat[xx];
    if (csum <= 0)
        csum = 1;

    /* 开始计算卷积 */
    prev = src->data + 4;
    curt = prev + src->bpl;
    next = curt + src->bpl;
    for (yy = 0; yy < hh; yy++)
    {
        for (xx = 0; xx < ww; xx++)
        {
            sint_t  bb, gg, rr;

            /* 第一排 */
            bb  = (sint_t)prev[(xx-1)*4+0] * mat[0];
            gg  = (sint_t)prev[(xx-1)*4+1] * mat[0];
            rr  = (sint_t)prev[(xx-1)*4+2] * mat[0];
            bb += (sint_t)prev[(xx+0)*4+0] * mat[1];
            gg += (sint_t)prev[(xx+0)*4+1] * mat[1];
            rr += (sint_t)prev[(xx+0)*4+2] * mat[1];
            bb += (sint_t)prev[(xx+1)*4+0] * mat[2];
            gg += (sint_t)prev[(xx+1)*4+1] * mat[2];
            rr += (sint_t)prev[(xx+1)*4+2] * mat[2];

            /* 第二排 */
            bb += (sint_t)curt[(xx-1)*4+0] * mat[3];
            gg += (sint_t)curt[(xx-1)*4+1] * mat[3];
            rr += (sint_t)curt[(xx-1)*4+2] * mat[3];
            bb += (sint_t)curt[(xx+0)*4+0] * mat[4];
            gg += (sint_t)curt[(xx+0)*4+1] * mat[4];
            rr += (sint_t)curt[(xx+0)*4+2] * mat[4];
            bb += (sint_t)curt[(xx+1)*4+0] * mat[5];
            gg += (sint_t)curt[(xx+1)*4+1] * mat[5];
            rr += (sint_t)curt[(xx+1)*4+2] * mat[5];

            /* 第三排 */
            bb += (sint_t)next[(xx-1)*4+0] * mat[6];
            gg += (sint_t)next[(xx-1)*4+1] * mat[6];
            rr += (sint_t)next[(xx-1)*4+2] * mat[6];
            bb += (sint_t)next[(xx+0)*4+0] * mat[7];
            gg += (sint_t)next[(xx+0)*4+1] * mat[7];
            rr += (sint_t)next[(xx+0)*4+2] * mat[7];
            bb += (sint_t)next[(xx+1)*4+0] * mat[8];
            gg += (sint_t)next[(xx+1)*4+1] * mat[8];
            rr += (sint_t)next[(xx+1)*4+2] * mat[8];

            /* 中心-B */
            bb /= csum;
            if (bb < 0)
                bb = 0;
            else
            if (bb > 255)
                bb = 255;
            *ptr++ = (byte_t)bb;

            /* 中心-G */
            gg /= csum;
            if (gg < 0)
                gg = 0;
            else
            if (gg > 255)
                gg = 255;
            *ptr++ = (byte_t)gg;

            /* 中心-R */
            rr /= csum;
            if (rr < 0)
                rr = 0;
            else
            if (rr > 255)
                rr = 255;
            *ptr++ = (byte_t)rr;

            /* 中心-A */
            *ptr++ = curt[xx * 4 + 3];
        }
        prev += src->bpl;
        curt += src->bpl;
        next += src->bpl;
    }
    return (dst);
}

/*
---------------------------------------
    回拷图片
---------------------------------------
*/
static void_t
conv3x3_back (
  __CR_IN__ const sIMAGE*   dst,
  __CR_IN__ const byte_t*   src
    )
{
    uint_t  hh;
    leng_t  bpl;
    byte_t* ptr;

    hh = dst->position.hh - 2;
    bpl = (dst->position.ww - 2) * 4;
    ptr = dst->data + dst->bpl + 4;
    for (; hh != 0; hh--) {
        mem_cpy(ptr, src, bpl);
        src += bpl;
        ptr += dst->bpl;
    }
}

/*
---------------------------------------
    图片卷积运算 (3 x 3)
---------------------------------------
*/
static bool_t
image_conv3x3 (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    uint_t  idx;
    ansi_t* str;
    byte_t* temp;
    sIMAGE* dest;
    sint_t  mat[9];

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    if (dest->fmt != CR_ARGB8888)
        return (TRUE);
    str = xml_attr_bufferU("mat", param);
    if (str == NULL ||
        str2lstA((uint_t*)mat, 9, str, "[],") == NULL) {
        for (idx = 0; idx < 9; idx++)
            mat[idx] = 1;
    }
    temp = conv3x3_main(dest, mat);
    if (temp == NULL)
        return (TRUE);
    conv3x3_back(dest, temp);
    mem_free(temp);
    return (TRUE);
}

/* SOBEL 的两个卷积矩阵 */
static const sint_t s_sobel_matx[9] =
{
    -1,  0,  1,
    -2,  0,  2,
    -1,  0,  1,
};
static const sint_t s_sobel_maty[9] =
{
     1,  2,  1,
     0,  0,  0,
    -1, -2, -1,
};

/*
---------------------------------------
    SOBEL 边缘检测
---------------------------------------
*/
static bool_t
image_edge_sobel (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    byte_t* gx;
    byte_t* gy;
    leng_t  idx;
    leng_t  size;
    sIMAGE* dest;

    CR_NOUSE(nouse);
    CR_NOUSE(param);
    dest = (sIMAGE*)image;
    if (dest->fmt != CR_ARGB8888)
        return (TRUE);
    gx = conv3x3_main(dest, s_sobel_matx);
    if (gx == NULL)
        return (TRUE);
    gy = conv3x3_main(dest, s_sobel_maty);
    if (gy == NULL) {
        mem_free(gx);
        return (TRUE);
    }

    /* 计算梯度图 */
    size  = dest->position.ww - 2;
    size *= dest->position.hh - 2;
    size *= sizeof(int32u);
    for (idx = 0; idx < size; idx += 4)
    {
        sint_t  tx, ty;

        /* 分量-B */
        tx = (sint_t)gx[idx + 0];
        ty = (sint_t)gy[idx + 0];
        tx *= tx;
        ty *= ty;
        ty += tx;
        tx = (sint_t)(sqrtf((float)ty) + 0.5f);
        if (tx < 0)
            tx = 0;
        else
        if (tx > 255)
            tx = 255;
        gx[idx + 0] = (byte_t)tx;

        /* 分量-G */
        tx = (sint_t)gx[idx + 1];
        ty = (sint_t)gy[idx + 1];
        tx *= tx;
        ty *= ty;
        ty += tx;
        tx = (sint_t)(sqrtf((float)ty) + 0.5f);
        if (tx < 0)
            tx = 0;
        else
        if (tx > 255)
            tx = 255;
        gx[idx + 1] = (byte_t)tx;

        /* 分量-R */
        tx = (sint_t)gx[idx + 2];
        ty = (sint_t)gy[idx + 2];
        tx *= tx;
        ty *= ty;
        ty += tx;
        tx = (sint_t)(sqrtf((float)ty) + 0.5f);
        if (tx < 0)
            tx = 0;
        else
        if (tx > 255)
            tx = 255;
        gx[idx + 2] = (byte_t)tx;
    }
    conv3x3_back(dest, gx);
    mem_free(gy);
    mem_free(gx);
    return (TRUE);
}

/*
---------------------------------------
    图片门限过滤
---------------------------------------
*/
static bool_t
image_cut_down (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    byte_t* ptr;
    byte_t* line;
    sIMAGE* dest;
    uint_t  gate;
    uint_t  ww, hh;

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    if (dest->fmt != CR_ARGB8888)
        return (TRUE);
    line = dest->data;
    ww = dest->position.ww;
    hh = dest->position.hh;
    gate = xml_attr_intxU("gate", 97, param);
    if (param->found)
    {
        /* 有参数使用指定参数 */
        for (uint_t yy = 0; yy < hh; yy++) {
            ptr = line;
            for (uint_t xx = 0; xx < ww; xx++) {
                if (ptr[0] <= gate) {
                    ptr[0] = 0;
                    ptr[1] = 0;
                    ptr[2] = 0;
                }
                ptr += sizeof(int32u);
            }
            line += dest->bpl;
        }
    }
    else
    {
        int64u  total = 0;

        /* 没有参数使用平均值 */
        for (uint_t yy = 0; yy < hh; yy++) {
            ptr = line;
            for (uint_t xx = 0; xx < ww; xx++) {
                total += ptr[0];
                ptr += sizeof(int32u);
            }
            line += dest->bpl;
        }
        total /= ww;
        total /= hh;
        gate = (uint_t)total;
        line = dest->data;
        for (uint_t yy = 0; yy < hh; yy++) {
            ptr = line;
            for (uint_t xx = 0; xx < ww; xx++) {
                if (ptr[0] <= gate) {
                    ptr[0] = 0;
                    ptr[1] = 0;
                    ptr[2] = 0;
                }
                ptr += sizeof(int32u);
            }
            line += dest->bpl;
        }
    }
    return (TRUE);
}

/*
---------------------------------------
    颜色距离的平方
---------------------------------------
*/
static int32u
distance_rgb (
  __CR_IN__ sint_t          wr,
  __CR_IN__ sint_t          wg,
  __CR_IN__ sint_t          wb,
  __CR_IN__ sint_t          wt,
  __CR_IN__ const byte_t*   p1,
  __CR_IN__ const byte_t*   p2
    )
{
    int32s  sm;
    int32s  bb = (int32s)p1[0];
    int32s  gg = (int32s)p1[1];
    int32s  rr = (int32s)p1[2];

    /* 空间距离 */
    bb -= (int32s)p2[0];
    sm  = (int32s)(wb * bb * bb);
    gg -= (int32s)p2[1];
    sm += (int32s)(wg * gg * gg);
    rr -= (int32s)p2[2];
    sm += (int32s)(wr * rr * rr);
    return ((int32u)(sm / wt));
}

/*
---------------------------------------
    生成色阶颜色表
---------------------------------------
*/
static byte_t*
create_step_rgb (
  __CR_IN__ uint_t  step,
  __CR_OT__ uint_t* size
    )
{
    uchar*  ptr;
    uchar*  table;
    uint_t  count;
    uint_t  delta;

    if (step < 2)
        step = 2;
    else
    if (step > 16)
        step = 16;
    count = step * step * step * 3;
    table = (uchar*)mem_malloc(count);
    if (table == NULL)
        return (NULL);
    ptr = table;
    delta = 255 / (step - 1);
    for (uint_t ir = 0; ir < step * delta; ir += delta) {
        for (uint_t ig = 0; ig < step * delta; ig += delta) {
            for (uint_t ib = 0; ib < step * delta; ib += delta) {
                *ptr++ = (byte_t)ib;
                *ptr++ = (byte_t)ig;
                *ptr++ = (byte_t)ir;
            }
        }
    }
    *size = count;
    return (table);
}

/*
---------------------------------------
    图片色阶过滤 (内部实现)
---------------------------------------
*/
static void_t
image_clr_step_int (
  __CR_IN__ sIMAGE*         dest,
  __CR_IN__ uint_t          size,
  __CR_IN__ const byte_t*   table,
  __CR_IN__ const sint_t    wrgb[3]
    )
{
    byte_t* ptr;
    byte_t* line;
    sint_t  wtot;
    uint_t  idxs;
    int32u  dist;
    int32u  mdst;
    uint_t  ww, hh;

    /* 统一到距离最近的颜色 */
    if (size % 3 != 0)
        return;
    line = dest->data;
    ww = dest->position.ww;
    hh = dest->position.hh;
    wtot = wrgb[0] + wrgb[1] + wrgb[2];
    if (wtot == 0) wtot = 1;
    for (uint_t yy = 0; yy < hh; yy++) {
        ptr = line;
        for (uint_t xx = 0; xx < ww; xx++) {
            idxs = 0;
            mdst = ((int32u)-1);
            for (uint_t ii = 0; ii < size; ii += 3) {
                dist = distance_rgb(wrgb[0], wrgb[1], wrgb[2],
                                    wtot, ptr, &table[ii]);
                if (dist < mdst) {
                    idxs = ii;
                    mdst = dist;
                }
            }
            ptr[0] = table[idxs + 0];
            ptr[1] = table[idxs + 1];
            ptr[2] = table[idxs + 2];
            ptr += sizeof(int32u);
        }
        line += dest->bpl;
    }
}

/*
---------------------------------------
    图片色阶过滤
---------------------------------------
*/
static bool_t
image_clr_step (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    sIMAGE* dest;
    byte_t* table;
    sint_t  wrgb[3];
    uint_t  size, step;

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    if (dest->fmt != CR_ARGB8888)
        return (TRUE);
    step = xml_attr_intxU("step", 2, param);
    table = create_step_rgb(step, &size);
    if (table == NULL)
        return (TRUE);
    wrgb[0] = (sint_t)xml_attr_intxU("wr", 2, param);
    wrgb[1] = (sint_t)xml_attr_intxU("wg", 4, param);
    wrgb[2] = (sint_t)xml_attr_intxU("wb", 1, param);
    image_clr_step_int(dest, size, table, wrgb);
    mem_free(table);
    return (TRUE);
}

/*
---------------------------------------
    图片乘法运算
---------------------------------------
*/
static bool_t
image_multiply (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    byte_t* ptr;
    byte_t* line;
    sIMAGE* dest;
    fp32_t  mult;
    fp32_t  fval;
    uint_t  uval;
    uint_t  ww, hh;

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    if (dest->fmt != CR_ARGB8888)
        return (TRUE);
    line = dest->data;
    ww = dest->position.ww;
    hh = dest->position.hh;
    mult = xml_attr_fp32U("factor", 2.0f, param);
    if (param->found)
    {
        /* 有参数使用指定参数 */
        for (uint_t yy = 0; yy < hh; yy++) {
            ptr = line;
            for (uint_t xx = 0; xx < ww; xx++) {
                fval = mult * ptr[0];
                if (fval >= 255.0f)
                    ptr[0] = 0xFF;
                else
                    ptr[0] = (byte_t)fval;
                fval = mult * ptr[1];
                if (fval >= 255.0f)
                    ptr[1] = 0xFF;
                else
                    ptr[1] = (byte_t)fval;
                fval = mult * ptr[2];
                if (fval >= 255.0f)
                    ptr[2] = 0xFF;
                else
                    ptr[2] = (byte_t)fval;
                ptr += sizeof(int32u);
            }
            line += dest->bpl;
        }
    }
    else
    {
        /* 没有参数使用乘方运算 */
        for (uint_t yy = 0; yy < hh; yy++) {
            ptr = line;
            for (uint_t xx = 0; xx < ww; xx++) {
                uval = ptr[0];
                uval *= uval;
                if (uval >= 0xFF)
                    ptr[0] = 0xFF;
                else
                    ptr[0] = (byte_t)uval;
                uval = ptr[1];
                uval *= uval;
                if (uval >= 0xFF)
                    ptr[1] = 0xFF;
                else
                    ptr[1] = (byte_t)uval;
                uval = ptr[2];
                uval *= uval;
                if (uval >= 0xFF)
                    ptr[2] = 0xFF;
                else
                    ptr[2] = (byte_t)uval;
                ptr += sizeof(int32u);
            }
            line += dest->bpl;
        }
    }
    return (TRUE);
}

/*
---------------------------------------
    图片查表过滤
---------------------------------------
*/
static bool_t
image_lookup (
  __CR_UU__ void_t*     nouse,
  __CR_IO__ void_t*     image,
  __CR_IN__ sXNODEu*    param
    )
{
    leng_t  size;
    sIMAGE* dest;
    ansi_t* data;
    sint_t  wrgb[3];
    byte_t  table[48];

    CR_NOUSE(nouse);
    dest = (sIMAGE*)image;
    if (dest->fmt != CR_ARGB8888)
        return (TRUE);
    data = xml_attr_bufferU("table", param);
    if (data == NULL)
        return (TRUE);
    size = sizeof(table);
    str2datA(table, &size, data);
    wrgb[0] = (sint_t)xml_attr_intxU("wr", 2, param);
    wrgb[1] = (sint_t)xml_attr_intxU("wg", 4, param);
    wrgb[2] = (sint_t)xml_attr_intxU("wb", 1, param);
    image_clr_step_int(dest, (uint_t)size, table, wrgb);
    return (TRUE);
}

/*
=======================================
    滤镜接口导出表
=======================================
*/
CR_API const sXC_PORT   qst_v2d_filter[] =
{
    { "crhack_and_x86", fill_and_x86 },
    { "crhack_orr_x86", fill_orr_x86 },
    { "crhack_not_x86", fill_not_x86 },
    { "crhack_xor_x86", fill_xor_x86 },
    { "crhack_add_x86", fill_add_x86 },
    { "crhack_sub_x86", fill_sub_x86 },
    { "crhack_lrp_x86", fill_lrp_x86 },
    { "crhack_flip_vv", flip_vertical },
    { "crhack_swap_rb", swap_red_blue },
    { "crhack_diffuse", image_diffuse },
    { "crhack_graying", image_graying },
    { "crhack_binaryz", image_binaryz },
    { "crhack_conv3x3", image_conv3x3 },
    { "crhack_sobel", image_edge_sobel },
    { "crhack_cutdown", image_cut_down },
    { "crhack_imgstep", image_clr_step },
    { "crhack_multiply", image_multiply },
    { "crhack_lookup", image_lookup },
    { NULL, NULL },
};
