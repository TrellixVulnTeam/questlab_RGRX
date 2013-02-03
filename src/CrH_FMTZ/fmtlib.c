/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2010-01-29  */
/*     #######          ###    ###      [CORE]      ###  ~~~~~~~~~~~~~~~~~~  */
/*    ########          ###    ###                  ###  MODIFY: 2013-02-02  */
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
/*  >>>>>>>>>>>>>>>>>>>>>>>> CrHack 文件格式函数库 <<<<<<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_FMTLIB_C__
#define __CR_FMTLIB_C__ 0x84834BAFUL

#include "hash.h"
#include "safe.h"
#include "fmtint.h"
#include "memlib.h"
#include "strlib.h"

/*****************************************************************************/
/*                               插件功能封装                                */
/*****************************************************************************/

/*
---------------------------------------
    使用文件名的扩展名作为键A
---------------------------------------
*/
static uint_t
match_findA (
  __CR_IN__ const void_t*   key
    )
{
    leng_t  idx, len;

    /* 注意: 文件名必须都小写 */
    len = str_lenA((ansi_t*)key);
    for (idx = len; idx != 0; idx--) {
        if (((ansi_t*)key)[idx - 1] == CR_AC('.')) {
            key = (void_t*)(&(((ansi_t*)key)[idx - 1]));
            return (hash_str_djb2(key, (len - idx + 1) * sizeof(ansi_t)));
        }
    }
    return (hash_str_djb2(key, 0));     /* 无扩展名或不确定 */
}

/*
---------------------------------------
    使用文件名的扩展名作为键W
---------------------------------------
*/
static uint_t
match_findW (
  __CR_IN__ const void_t*   key
    )
{
    leng_t  idx, len;

    /* 注意: 文件名必须都小写 */
    len = str_lenW((wide_t*)key);
    for (idx = len; idx != 0; idx--) {
        if (((wide_t*)key)[idx - 1] == CR_WC('.')) {
            key = (void_t*)(&(((wide_t*)key)[idx - 1]));
            return (hash_str_djb2(key, (len - idx + 1) * sizeof(wide_t)));
        }
    }
    return (hash_str_djb2(key, 0));     /* 无扩展名或不确定 */
}

/*
---------------------------------------
    使用通配符匹配文件名A
---------------------------------------
*/
static bool_t
match_compA (
  __CR_IN__ const void_t*   key,
  __CR_IN__ const void_t*   obj
    )
{
    const sMATCHa*  unit = (sMATCHa*)obj;

    return (wildcard_matchIA((ansi_t*)key, unit->match));
}

/*
---------------------------------------
    使用通配符匹配文件名W
---------------------------------------
*/
static bool_t
match_compW (
  __CR_IN__ const void_t*   key,
  __CR_IN__ const void_t*   obj
    )
{
    const sMATCHw*  unit = (sMATCHw*)obj;

    return (wildcard_matchIW((wide_t*)key, unit->match));
}

/*
=======================================
    释放引擎插件
=======================================
*/
CR_API void_t
engine_free (
  __CR_IN__ sENGINE*    engine
    )
{
    sENGINE_INT*    real;

    real = (sENGINE_INT*)engine;
    if (engine->engine_free != NULL)
        engine->engine_free(engine);
    curtain_freeT(&real->m_wide, sMATCHw);
    curtain_freeT(&real->m_ansi, sMATCHa);
    if (engine->sbin != NULL)
        sbin_unload(engine->sbin);
    mem_free(engine);
}

/*
=======================================
    初始化引擎插件
=======================================
*/
CR_API sENGINE*
engine_init (
  __CR_IN__ const sMATCHa*  ansi,
  __CR_IN__ const sMATCHw*  wide,
  __CR_IN__ uint_t          count
    )
{
    uint_t          index;
    sENGINE_INT*    engine;

    engine = struct_new(sENGINE_INT);
    if (engine == NULL) {
        err_set(__CR_FMTLIB_C__, CR_NULL,
                "engine_init()", "struct_new() failure");
        return (NULL);
    }
    struct_zero(engine, sENGINE_INT);

    /* 生成两个哈希表 */
    if (ansi != NULL) {
        if (!curtain_initT(&engine->m_ansi, sMATCHa, count, 0)) {
            err_set(__CR_FMTLIB_C__, FALSE,
                    "engine_init()", "curtain_initT() failure");
            goto _failure1;
        }
        engine->m_ansi.find = match_findA;
        engine->m_ansi.comp = match_compA;
    }
    if (wide != NULL) {
        if (!curtain_initT(&engine->m_wide, sMATCHw, count, 0)) {
            err_set(__CR_FMTLIB_C__, FALSE,
                    "engine_init()", "curtain_initT() failure");
            goto _failure2;
        }
        engine->m_wide.find = match_findW;
        engine->m_wide.comp = match_compW;
    }

    /* 注册文件类型匹配 */
    for (index = 0; index < count; index++)
    {
        if (ansi != NULL) {
            if (curtain_insertT(&engine->m_ansi, sMATCHa,
                            ansi[index].filext, &ansi[index]) == NULL) {
                err_set(__CR_FMTLIB_C__, CR_NULL,
                        "engine_init()", "curtain_insertT() failure");
                goto _failure3;
            }
        }
        if (wide != NULL) {
            if (curtain_insertT(&engine->m_wide, sMATCHw,
                            wide[index].filext, &wide[index]) == NULL) {
                err_set(__CR_FMTLIB_C__, CR_NULL,
                        "engine_init()", "curtain_insertT() failure");
                goto _failure3;
            }
        }
    }
    engine->engine.mask = CR_FMTZ_MASK_ALL;
    return ((sENGINE*)engine);

_failure3:
    curtain_freeT(&engine->m_wide, sMATCHw);
_failure2:
    curtain_freeT(&engine->m_ansi, sMATCHa);
_failure1:
    mem_free(engine);
    return (NULL);
}

/*
=======================================
    文件格式模式匹配
=======================================
*/
CR_API bool_t
fmtz_find (
  __CR_IN__ sENGINE*    engine,
  __CR_IO__ sLOADER*    loader
    )
{
    ansi_t*         name_a;
    wide_t*         name_w;
    void_t*         match = NULL;
    sENGINE_INT*    real = (sENGINE_INT*)engine;

    /* 清除上次结果 */
    loader->nprm = NULL;

    /* 单字节匹配优先 */
    if (loader->name.ansi != NULL) {
        name_a = str_dupA(loader->name.ansi);
        if (name_a == NULL) {
            err_set(__CR_FMTLIB_C__, CR_NULL,
                    "fmtz_find()", "str_dupA() failure");
            return (FALSE);
        }
        flname_extractA(name_a, loader->name.ansi);
        str_lwrA(name_a);
        match = curtain_findT(&real->m_ansi, sMATCHa, name_a);
        mem_free(name_a);
    }
    else
    if (loader->name.wide != NULL) {
        name_w = str_dupW(loader->name.wide);
        if (name_w == NULL) {
            err_set(__CR_FMTLIB_C__, CR_NULL,
                    "fmtz_find()", "str_dupW() failure");
            return (FALSE);
        }
        flname_extractW(name_w, loader->name.wide);
        str_lwrW(name_w);
        match = curtain_findT(&real->m_wide, sMATCHw, name_w);
        mem_free(name_w);
    }

    /* 需要判断一下掩码 */
    if ((match != NULL) &&
        (((sMATCHa*)match)->maskz & engine->mask)) {
        loader->nprm = (void_t*)(((sMATCHa*)match)->loader);
        return (TRUE);
    }
    return (FALSE);
}

/*
=======================================
    加载多类型文件 (返回匹配项)
=======================================
*/
CR_API sFMTZ*
fmtz_load (
  __CR_IO__ iDATIN*         datin,
  __CR_IN__ const sTRY_LDR* ldrs,
  __CR_IN__ uint_t          count,
  __CR_IO__ sLOADER*        param,
  __CR_IN__ int32u          maskz
    )
{
    sFMTZ*  fmtz;
    uint_t  cnts;
    fsize_t back;

    /* 保存初始位置 */
    back = CR_VCALL(datin)->tell(datin);
    if (back == (fsize_t)-1) {
        err_set(__CR_FMTLIB_C__, -1L,
                "fmtz_load()", "iDATIN::tell() failure");
        return (NULL);
    }

    for (cnts = 0; cnts < count; cnts++)
    {
        /* 跳过非期望类型 */
        if (!(ldrs[cnts].mask & maskz))
            continue;
        fmtz = ((load_fmtz_t)(ldrs[cnts].func))(datin, param);
        if (fmtz != NULL) {
            param->nprm = (void_t*)(ldrs[cnts].func);   /* 设置匹配项 */
            return (fmtz);
        }

        /* 定位到初始位置 */
        if (!CR_VCALL(datin)->seek(datin, back, SEEK_SET)) {
            err_set(__CR_FMTLIB_C__, FALSE,
                    "fmtz_load()", "iDATIN::seek() failure");
            return (NULL);
        }
    }
    param->nprm = NULL;     /* 无匹配项, 设为 NULL */
    return (NULL);
}

/*
=======================================
    释放读取的文件数据
=======================================
*/
CR_API bool_t
fmtz_free (
  __CR_IN__ const sFMTZ*    fmtz
    )
{
    int32u          idx;
    const sFMT_DAT* fmt_dat;
    const sFMT_PIC* fmt_pic;
    const sFMT_RCT* fmt_rct;
    const sFMT_TXT* fmt_txt;
    const sFMT_PRT* fmt_prt;

    switch (fmtz->type)
    {
        /* 释放数据文件 */
        case CR_FMTZ_NOP:
        case CR_FMTZ_DEC:
            fmt_dat = (const sFMT_DAT*)fmtz;
            TRY_FREE(fmt_dat->data)
            break;

        /* 释放图片文件 */
        case CR_FMTZ_PIC:
            fmt_pic = (const sFMT_PIC*)fmtz;
            for (idx = 0; idx < fmt_pic->count; idx++)
                image_del(fmt_pic->frame[idx].pic);
            mem_free(fmt_pic->frame);
            break;

        /* 释放区域文件 */
        case CR_FMTZ_RCT:
            fmt_rct = (const sFMT_RCT*)fmtz;
            TRY_FREE(fmt_rct->pict)
            break;

        /* 释放文本文件 */
        case CR_FMTZ_TXT:
            fmt_txt = (const sFMT_TXT*)fmtz;
            TRY_FREE(fmt_txt->text)
            break;

        /* 释放对象文件 */
        case CR_FMTZ_PRT:
            fmt_prt = (const sFMT_PRT*)fmtz;
            CR_VCALL(fmt_prt->port)->release(fmt_prt->port);
            break;

        default:
            err_set(__CR_FMTLIB_C__, fmtz->type,
                    "fmtz_free()", "invalid param: fmtz->type");
            return (FALSE);
    }
    mem_free(fmtz);
    return (TRUE);
}

/*
=======================================
    获取指定图片帧对象
=======================================
*/
CR_API sIMAGE*
fmtz_get_pic (
  __CR_IN__ const sFMTZ*    fmtz,
  __CR_IN__ int32u          index
    )
{
    const sFMT_PIC* fmt_pic;

    if (fmtz->type != CR_FMTZ_PIC) {
        err_set(__CR_FMTLIB_C__, fmtz->type,
                "fmtz_get_pic()", "invalid param: fmtz->type");
        return (NULL);
    }
    fmt_pic = (const sFMT_PIC*)fmtz;
    if (index >= fmt_pic->count) {
        err_set(__CR_FMTLIB_C__, index,
                "fmtz_get_pic()", "index: out of bounds");
        return (NULL);
    }
    return (fmt_pic->frame[index].pic);
}

/*****************************************************************************/
/*                               读包功能封装                                */
/*****************************************************************************/

/*
---------------------------------------
    查找成员索引回调
---------------------------------------
*/
static uint_t
finder_find (
  __CR_IN__ const void_t*   key
    )
{
    return (hash_str_djb2(key, str_lenA((ansi_t*)key)));
}

/*
---------------------------------------
    查找成员比较回调
---------------------------------------
*/
static bool_t
finder_comp (
  __CR_IN__ const void_t*   key,
  __CR_IN__ const void_t*   obj
    )
{
    sFINDER*    unit = (sFINDER*)obj;

    return (str_cmpA(unit->finfo->find, (ansi_t*)key) == 0);
}

/*
=======================================
    初始化文件查找表
=======================================
*/
CR_API bool_t
pack_init_list (
  __CR_IO__ iPACKAGE*   pack,
  __CR_IN__ bool_t      caseless
    )
{
    int64u      idx;
    int64u      num;
    leng_t      cnt;
    sFINDER     tmp;
    sPAK_FILE*  ptr;

    num = pack_file_num(pack);
    if (cut_int64u(&cnt, num)) {
        err_set(__CR_FMTLIB_C__, num,
                "pack_init_list()", "<file_num> truncated");
        return (FALSE);
    }
    if (!curtain_initT(&pack->__search__, sFINDER, cnt, 0)) {
        err_set(__CR_FMTLIB_C__, FALSE,
                "pack_init_list()", "curtain_initT() failure");
        return (FALSE);
    }
    pack->__caseless__ = caseless;
    pack->__search__.find = finder_find;
    pack->__search__.comp = finder_comp;

    if (pack->__filelst__ == NULL)
        return (TRUE);
    ptr = pack->__filelst__;
    for (idx = 0; idx < num; idx++) {
        tmp.index = idx;
        tmp.finfo = ptr;
        if (ptr->find == NULL) {
            ptr->find = str_dupA(ptr->name);
            if (ptr->find == NULL) {
                err_set(__CR_FMTLIB_C__, CR_NULL,
                        "pack_init_list()", "str_dupA() failure");
                curtain_freeT(&pack->__search__, sFINDER);
                return (FALSE);
            }
            if (caseless)
                flname_uniqueA((ansi_t*)ptr->find);
            else
                path_uniqueA((ansi_t*)ptr->find);
        }
        if (curtain_insertT(&pack->__search__, sFINDER,
                            ptr->find, &tmp) == NULL) {
            err_set(__CR_FMTLIB_C__, CR_NULL,
                    "pack_init_list()", "curtain_insertT() failure");
            curtain_freeT(&pack->__search__, sFINDER);
            return (FALSE);
        }
        ptr = (sPAK_FILE*)((byte_t*)ptr + ptr->skip);
    }
    return (TRUE);
}

/*
=======================================
    释放文件查找表
=======================================
*/
CR_API void_t
pack_free_list (
  __CR_IN__ iPACKAGE*   pack
    )
{
    curtain_freeT(&pack->__search__, sFINDER);
}

/*
=======================================
    文件名到索引的查找U
=======================================
*/
CR_API bool_t
pack_find_fileU (
  __CR_IO__ iPACKAGE*       pack,
  __CR_OT__ int64u*         index,
  __CR_IN__ const ansi_t*   name
    )
{
    ansi_t*     find;
    sFINDER*    unit;

    /* 统一文件目录风格 */
    find = str_dupA(name);
    if (find == NULL) {
        err_set(__CR_FMTLIB_C__, CR_NULL,
                "pack_find_fileU()", "str_dupA() failure");
        return (FALSE);
    }
    if (pack->__caseless__)
        flname_uniqueA(find);
    else
        path_uniqueA(find);
    unit = curtain_findT(&pack->__search__, sFINDER, find);
    mem_free(find);
    if (unit == NULL)
        return (FALSE);
    if (index != NULL)
       *index  = unit->index;
    return (TRUE);
}

/*
=======================================
    文件名到索引的查找W
=======================================
*/
CR_API bool_t
pack_find_fileW (
  __CR_IO__ iPACKAGE*       pack,
  __CR_OT__ int64u*         index,
  __CR_IN__ const wide_t*   name
    )
{
    bool_t  rett;
    ansi_t* utf8;

    utf8 = utf16_to_utf8(name);
    if (utf8 == NULL) {
        err_set(__CR_FMTLIB_C__, CR_NULL,
                "pack_find_fileW()", "utf16_to_utf8() failure");
        return (FALSE);
    }
    rett = pack_find_fileU(pack, index, utf8);
    mem_free(utf8);
    return (rett);
}

/*
=======================================
    文件名到索引的查找A
=======================================
*/
CR_API bool_t
pack_find_fileA (
  __CR_IO__ iPACKAGE*       pack,
  __CR_OT__ int64u*         index,
  __CR_IN__ const ansi_t*   name,
  __CR_IN__ uint_t          cpage
    )
{
    bool_t  rett;
    ansi_t* utf8;

    utf8 = local_to_utf8(cpage, name);
    if (utf8 == NULL) {
        err_set(__CR_FMTLIB_C__, CR_NULL,
                "pack_find_fileA()", "local_to_utf8() failure");
        return (FALSE);
    }
    rett = pack_find_fileU(pack, index, utf8);
    mem_free(utf8);
    return (rett);
}

/*
=======================================
    读取文件个数
=======================================
*/
CR_API int64u
pack_file_num (
  __CR_IO__ iPACKAGE*   pack
    )
{
    return (CR_VCALL(pack)->getFileNum(pack));
}

/*
=======================================
    读取文件数据 (根据索引)
=======================================
*/
CR_API bool_t
pack_file_data (
  __CR_IO__ iPACKAGE*   pack,
  __CR_OT__ sBUFFER*    buff,
  __CR_IN__ int64u      index,
  __CR_IN__ bool_t      hash
    )
{
    return (CR_VCALL(pack)->getFileData(pack, buff, index, hash));
}

/*
=======================================
    读取文件信息 (根据索引)
=======================================
*/
CR_API bool_t
pack_file_info (
  __CR_IO__ iPACKAGE*   pack,
  __CR_OT__ sPAK_FILE** info,
  __CR_IN__ int64u      index
    )
{
    return (CR_VCALL(pack)->getFileInfo(pack, info, index));
}

/*
=======================================
    读取文件数据U (根据名称)
=======================================
*/
CR_API bool_t
pack_file_dataU (
  __CR_IO__ iPACKAGE*       pack,
  __CR_OT__ sBUFFER*        buff,
  __CR_IN__ const ansi_t*   name,
  __CR_IN__ bool_t          hash
    )
{
    int64u  index;

    if (!pack_find_fileU(pack, &index, name))
        return (FALSE);
    return (pack_file_data(pack, buff, index, hash));
}

/*
=======================================
    读取文件数据W (根据名称)
=======================================
*/
CR_API bool_t
pack_file_dataW (
  __CR_IO__ iPACKAGE*       pack,
  __CR_OT__ sBUFFER*        buff,
  __CR_IN__ const wide_t*   name,
  __CR_IN__ bool_t          hash
    )
{
    int64u  index;

    if (!pack_find_fileW(pack, &index, name))
        return (FALSE);
    return (pack_file_data(pack, buff, index, hash));
}

/*
=======================================
    读取文件数据A (根据名称)
=======================================
*/
CR_API bool_t
pack_file_dataA (
  __CR_IO__ iPACKAGE*       pack,
  __CR_OT__ sBUFFER*        buff,
  __CR_IN__ const ansi_t*   name,
  __CR_IN__ uint_t          cpage,
  __CR_IN__ bool_t          hash
    )
{
    int64u  index;

    if (!pack_find_fileA(pack, &index, name, cpage))
        return (FALSE);
    return (pack_file_data(pack, buff, index, hash));
}

/*
=======================================
    读取文件信息U (根据名称)
=======================================
*/
CR_API bool_t
pack_file_infoU (
  __CR_IO__ iPACKAGE*       pack,
  __CR_OT__ sPAK_FILE**     info,
  __CR_IN__ const ansi_t*   name
    )
{
    int64u  index;

    if (!pack_find_fileU(pack, &index, name))
        return (FALSE);
    return (pack_file_info(pack, info, index));
}

/*
=======================================
    读取文件信息W (根据名称)
=======================================
*/
CR_API bool_t
pack_file_infoW (
  __CR_IO__ iPACKAGE*       pack,
  __CR_OT__ sPAK_FILE**     info,
  __CR_IN__ const wide_t*   name
    )
{
    int64u  index;

    if (!pack_find_fileW(pack, &index, name))
        return (FALSE);
    return (pack_file_info(pack, info, index));
}

/*
=======================================
    读取文件信息A (根据名称)
=======================================
*/
CR_API bool_t
pack_file_infoA (
  __CR_IO__ iPACKAGE*       pack,
  __CR_OT__ sPAK_FILE**     info,
  __CR_IN__ const ansi_t*   name,
  __CR_IN__ uint_t          cpage
    )
{
    int64u  index;

    if (!pack_find_fileA(pack, &index, name, cpage))
        return (FALSE);
    return (pack_file_info(pack, info, index));
}

#endif  /* !__CR_FMTLIB_C__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
