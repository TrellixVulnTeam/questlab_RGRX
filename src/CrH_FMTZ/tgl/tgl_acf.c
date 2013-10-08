/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2013-10-08  */
/*     #######          ###    ###      [FMTZ]      ###  ~~~~~~~~~~~~~~~~~~  */
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
/*  >>>>>>>>>>>>>>>>>>>> CrHack TGL ACF 图片读取函数库 <<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_TGL_ACF_C__
#define __CR_TGL_ACF_C__ 0xF11F7FBAUL

#include "pixels.h"
#include "strlib.h"
#include "fmtz/tgl.h"

/* ACF 内部结构 (LE) */
#ifndef _CR_NO_PRAGMA_PACK_
    #pragma pack (push, 1)
#endif

/* ACF 图片项结构 */
CR_TYPEDEF struct
{
        int32u  offset;     /* 数据相对偏移 */
        int16u  ww, hh;     /* 子图像的宽高 */
        int16u  cx, cy;     /* 图像基准坐标 */

} CR_PACKED sACF_IDX;

#ifndef _CR_NO_PRAGMA_PACK_
    #pragma pack (pop)
#endif

/* 接口内部数据结构 */
typedef struct
{
        /* 通用部分 */
        iPICTURE    pics;

        /* 个性部分 */
        uint_t      m_type;
        bool_t      m_flip;
        byte_t*     m_dats;
        sACF_IDX*   m_attr;
        byte_t      m_pal[1024];

} iPIC_ACF;

/*
---------------------------------------
    释放接口
---------------------------------------
*/
static void_t
iPIC_ACF_release (
  __CR_IN__ iPICTURE*   that
    )
{
    iPIC_ACF*   real;

    real = (iPIC_ACF*)that;
    mem_free(real->m_dats);
    mem_free(real->m_attr);
    mem_free(that);
}

/*
---------------------------------------
    扩展接口
---------------------------------------
*/
static void_t*
iPIC_ACF_getMore (
  __CR_IN__ iPICTURE*   that,
  __CR_IN__ port_t      iid
    )
{
    /* 判断一下名称 */
    if (str_cmpA(iid, "iPICTURE::TGL_ACF") != 0)
        return (NULL);
    return ((void_t*)that);
}

/*
---------------------------------------
    获取图片帧
---------------------------------------
*/
static sFMT_PIC*
iPIC_ACF_get (
  __CR_IN__ iPICTURE*   that,
  __CR_IN__ int32u      index
    )
{
    int16u      line;
    byte_t*     dest;
    byte_t*     img8;
    iPIC_ACF*   real;
    sFMT_PIC*   rett;
    sACF_IDX*   attr;
    sFMT_FRAME  temp;

    /* 帧号过滤 */
    if (index >= that->__count__) {
        err_set(__CR_TGL_ACF_C__, index,
                "iPICTURE::get()", "index: out of bounds");
        return (NULL);
    }

    /* 生成图片对象 */
    real = (iPIC_ACF*)that;
    mem_zero(temp.wh, sizeof(temp.wh));
    temp.fmt = CR_PIC_PALS;
    temp.bpp = 8;
    temp.clr = "P";
    temp.wh[0] = 8;
    attr = &real->m_attr[index];
    temp.pic = image_new(0, 0, attr->ww, attr->hh, CR_INDEX8,
                         real->m_flip, 4);
    if (temp.pic == NULL) {
        err_set(__CR_TGL_ACF_C__, CR_NULL,
                "iPICTURE::get()", "image_new() failure");
        return (NULL);
    }

    /* 读取图形数据 */
    dest = temp.pic->data;
    img8 = real->m_dats + attr->offset;
    for (line = attr->hh; line != 0; line--) {
        mem_cpy(dest, img8, attr->ww);
        img8 += attr->ww;
        dest += temp.pic->bpl;
    }
    mem_cpy(temp.pic->pal, real->m_pal, 1024);

    /* 返回读取的文件数据 */
    rett = struct_new(sFMT_PIC);
    if (rett == NULL) {
        err_set(__CR_TGL_ACF_C__, CR_NULL,
                "iPICTURE::get()", "struct_new() failure");
        goto _failure;
    }
    rett->frame = struct_dup(&temp, sFMT_FRAME);
    if (rett->frame == NULL) {
        err_set(__CR_TGL_ACF_C__, CR_NULL,
                "iPICTURE::get()", "struct_dup() failure");
        mem_free(rett);
        goto _failure;
    }
    rett->type = CR_FMTZ_PIC;
    rett->count = 1;
    if (real->m_type == 0)
        rett->infor = "TGL ACF Image File (0FCA)";
    else
    if (real->m_type == 1)
        rett->infor = "TGL ACF Image File (1FCA)";
    else
        rett->infor = "TGL ACF Image File (2FCA)";
    return (rett);

_failure:
    image_del(temp.pic);
    return (NULL);
}

/* 接口虚函数表 */
static const iPICTURE_vtbl _rom_ s_pics_vtbl =
{
    iPIC_ACF_release, iPIC_ACF_getMore, iPIC_ACF_get,
};

/*
=======================================
    TGL ACF 文件读取
=======================================
*/
CR_API sFMT_PRT*
load_tgl_acf (
  __CR_IO__ iDATIN*         datin,
  __CR_IN__ const sLOADER*  param
    )
{
    uint_t      type;
    int32u      cnts;
    int32u      pals;
    int32u      vals;
    leng_t      read;
    leng_t      size;
    byte_t*     file;
    byte_t*     dats;
    fsize_t     flsz;
    sACF_IDX*   attr;
    sFMT_PRT*   rett;
    iPIC_ACF*   port;
    byte_t      pair[2];

    /* 这个参数可能为空 */
    if (datin == NULL) {
        err_set(__CR_TGL_ACF_C__, CR_NULL,
                "load_tgl_acf()", "invalid param: datin");
        return (NULL);
    }

    /* 读取 & 检查头部 */
    if (!CR_VCALL(datin)->getd_no(datin, &vals)) {
        err_set(__CR_TGL_ACF_C__, FALSE,
                "load_tgl_acf()", "iDATIN::getd_no() failure");
        return (NULL);
    }
    if (vals == mk_tag4("0FCA")) {
        file = NULL;
        type = 0;   /* 无压缩，颠倒 */
    }
    else
    if (vals == mk_tag4("1FCA")) {
        if (!CR_VCALL(datin)->getd_le(datin, &vals)) {
            err_set(__CR_TGL_ACF_C__, FALSE,
                    "load_tgl_acf()", "iDATIN::getd_le() failure");
            return (NULL);
        }
        if ((int32s)vals <= 0) {
            err_set(__CR_TGL_ACF_C__, vals,
                    "load_tgl_acf()", "invalid ACF format");
            return (NULL);
        }
        file = (byte_t*)mem_malloc32(vals + 8);
        if (file == NULL) {
            err_set(__CR_TGL_ACF_C__, CR_NULL,
                    "load_tgl_acf()", "mem_malloc32() failure");
            return (NULL);
        }
        dats = file + 8;
        for (cnts = vals; cnts != 0;) {
            if (!CR_VCALL(datin)->getb_no(datin, pair)) {
                err_set(__CR_TGL_ACF_C__, FALSE,
                        "load_tgl_acf()", "iDATIN::getb_no() failure");
                mem_free(file);
                return (NULL);
            }

            /* RLE 解码 */
            if (pair[0] != 0xFF) {
                type = 1;
            }
            else {
                read = CR_VCALL(datin)->read(datin, pair, 2);
                if (read != 2) {
                    err_set(__CR_TGL_ACF_C__, read,
                            "load_tgl_acf()", "iDATIN::read() failure");
                    mem_free(file);
                    return (NULL);
                }
                if (pair[1] == 0)
                    type = 256;
                else
                    type = pair[1];
            }

            for (; type != 0; type--) {
                *dats++ = pair[0];
                cnts -= 1;
                if (cnts == 0)
                    break;
            }
        }
        vals += 8;

        /* 生成一个内存文件对象 */
        datin = create_buff_in(file, (leng_t)vals, TRUE);
        if (datin == NULL) {
            err_set(__CR_TGL_ACF_C__, CR_NULL,
                    "load_tgl_acf()", "create_buff_in() failure");
            mem_free(file);
            return (NULL);
        }
        type = 1;   /* RLE 压缩，颠倒 */
    }
    else
    if (vals == mk_tag4("2FCA")) {
        file = NULL;
        type = 2;   /* 无压缩，不颠倒 */
    }
    else {
        err_set(__CR_TGL_ACF_C__, vals,
                "load_tgl_acf()", "invalid ACF format");
        return (NULL);
    }

    /* 读取调色板大小 */
    if (!CR_VCALL(datin)->seek(datin, 20, SEEK_SET)) {
        err_set(__CR_TGL_ACF_C__, FALSE,
                "load_tgl_acf()", "iDATIN::seek() failure");
        goto _failure1;
    }
    if (!CR_VCALL(datin)->getd_le(datin, &pals)) {
        err_set(__CR_TGL_ACF_C__, FALSE,
                "load_tgl_acf()", "iDATIN::getd_le() failure");
        goto _failure1;
    }
    if (pals == 0 || pals > 1024 || pals % 4 != 0) {
        err_set(__CR_TGL_ACF_C__, pals,
                "load_tgl_acf()", "invalid ACF format");
        goto _failure1;
    }
    flsz = dati_get_size(datin);
    if (flsz <= 72 + pals) {
        err_set(__CR_TGL_ACF_C__, pals,
                "load_tgl_acf()", "invalid ACF format");
        goto _failure1;
    }
    flsz -= 72 + pals;

    /* 读取图片索引大小 */
    if (!CR_VCALL(datin)->seek(datin, 36, SEEK_SET)) {
        err_set(__CR_TGL_ACF_C__, FALSE,
                "load_tgl_acf()", "iDATIN::seek() failure");
        goto _failure1;
    }
    if (!CR_VCALL(datin)->getd_le(datin, &cnts)) {
        err_set(__CR_TGL_ACF_C__, FALSE,
                "load_tgl_acf()", "iDATIN::getd_le() failure");
        goto _failure1;
    }
    if (cnts == 0 || flsz <= cnts ||
        cnts % sizeof(sACF_IDX) != 0) {
        err_set(__CR_TGL_ACF_C__, cnts,
                "load_tgl_acf()", "invalid ACF format");
        goto _failure1;
    }
    flsz -= cnts;
    cnts /= sizeof(sACF_IDX);

    /* 读取所有帧属性数据 */
    if (!CR_VCALL(datin)->seek(datin, 72 + pals, SEEK_SET)) {
        err_set(__CR_TGL_ACF_C__, FALSE,
                "load_tgl_acf()", "iDATIN::seek() failure");
        goto _failure1;
    }
    attr = mem_talloc32(cnts, sACF_IDX);
    if (attr == NULL) {
        err_set(__CR_TGL_ACF_C__, CR_NULL,
                "load_tgl_acf()", "mem_talloc32() failure");
        goto _failure1;
    }
    for (vals = 0; vals < cnts; vals++) {
        read = CR_VCALL(datin)->read(datin, &attr[vals], sizeof(sACF_IDX));
        if (read != sizeof(sACF_IDX)) {
            err_set(__CR_TGL_ACF_C__, read,
                    "load_tgl_acf()", "iDATIN::read() failure");
            goto _failure2;
        }

        /* 跳过非法的废帧 */
        attr[vals].offset = DWORD_LE(attr[vals].offset);
        if (attr[vals].offset >= flsz ||
            attr[vals].ww == 0 || attr[vals].hh == 0) {
            vals -= 1;  cnts -= 1;
            continue;
        }
        attr[vals].ww = WORD_LE(attr[vals].ww);
        attr[vals].hh = WORD_LE(attr[vals].hh);
        attr[vals].cx = WORD_LE(attr[vals].cx);
        attr[vals].cy = WORD_LE(attr[vals].cy);
    }

    /* 空图片检查 */
    if (cnts == 0) {
        err_set(__CR_TGL_ACF_C__, cnts,
                "load_tgl_acf()", "invalid ACF format");
        goto _failure2;
    }

    /* 读取所有图片帧数据 */
    dats = CR_VCALL(datin)->get(datin, &size, FALSE);
    if (dats == NULL) {
        err_set(__CR_TGL_ACF_C__, CR_NULL,
                "load_tgl_acf()", "iDATIN::get() failure");
        goto _failure2;
    }
    if (size < flsz) {
        err_set(__CR_TGL_ACF_C__, size,
                "load_tgl_acf()", "invalid ACF format");
        goto _failure3;
    }

    /* 定位到调色板数据 */
    if (!CR_VCALL(datin)->seek(datin, 72, SEEK_SET)) {
        err_set(__CR_TGL_ACF_C__, FALSE,
                "load_tgl_acf()", "iDATIN::seek() failure");
        goto _failure3;
    }

    /* 生成多帧图片接口对象 */
    port = struct_new(iPIC_ACF);
    if (port == NULL) {
        err_set(__CR_TGL_ACF_C__, CR_NULL,
                "load_tgl_acf()", "struct_new() failure");
        goto _failure3;
    }
    struct_zero(port, iPIC_ACF);
    port->m_type = type;
    port->m_dats = dats;
    port->m_attr = attr;
    port->pics.__count__ = cnts;
    port->pics.__vptr__ = &s_pics_vtbl;

    /* 读取全局调色板数据 */
    read = CR_VCALL(datin)->read(datin, port->m_pal, (leng_t)pals);
    if (read != (leng_t)pals) {
        err_set(__CR_TGL_ACF_C__, read,
                "load_tgl_acf()", "iDATIN::read() failure");
        mem_free(port);
        goto _failure3;
    }
    if (file != NULL)
        CR_VCALL(datin)->release(datin);
    pals /= sizeof(int32u);
    pal_4b_alp_sw(port->m_pal, FALSE, 0xFF, (uint_t)pals);

    /* 返回读取的文件数据 */
    rett = struct_new(sFMT_PRT);
    if (rett == NULL) {
        err_set(__CR_TGL_ACF_C__, CR_NULL,
                "load_tgl_acf()", "struct_new() failure");
        iPIC_ACF_release((iPICTURE*)port);
        return (NULL);
    }
    CR_NOUSE(param);
    rett->type = CR_FMTZ_PRT;
    rett->port = (iPORT*)port;
    rett->more = "iPICTURE";
    if (port->m_type == 0) {
        port->m_flip = TRUE;
        rett->infor = "TGL ACF Image File (0FCA)";
    }
    else
    if (port->m_type == 1) {
        port->m_flip = TRUE;
        rett->infor = "TGL ACF Image File (1FCA)";
    }
    else {
        port->m_flip = FALSE;
        rett->infor = "TGL ACF Image File (2FCA)";
    }
    return (rett);

_failure3:
    mem_free(dats);
_failure2:
    mem_free(attr);
_failure1:
    if (file != NULL)
        CR_VCALL(datin)->release(datin);
    return (NULL);
}

#endif  /* !__CR_TGL_ACF_C__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
