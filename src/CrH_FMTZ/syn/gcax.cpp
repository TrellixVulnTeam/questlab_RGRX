/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2012-09-12  */
/*     #######          ###    ###      [FMTZ]      ###  ~~~~~~~~~~~~~~~~~~  */
/*    ########          ###    ###                  ###  MODIFY: 2013-01-30  */
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
/*  >>>>>>>>>>>>>>>>>>>>>> CrHack GCA 封包读取函数库 <<<<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_GCAX_CPP__
#define __CR_GCAX_CPP__ 0xAAA5B9D8UL

#include "strlib.h"
#include "../fmtint.h"

#include "fmtz/syn.h"
#if defined(_CR_HAVE_PAK_GCA_)
#include "gcasdk/GcaSDK.h"

/* GcaSDK 导入库 */
#if (_CR_CC_VER_ == 1200)
    #pragma comment (lib, "GcaSDK_vc6.lib")
#else
    #pragma comment (lib, "GcaSDK_vc7.lib")
#endif

/* 接口内部数据结构 */
typedef struct
{
        /* 通用部分 */
        iPACKAGE    pack;

        /* 个性部分 */
        CGca*   m_gca;  /* 文件对象 */
        uint_t  m_cnt;  /* 文件个数 */
        ansi_t* m_str;  /* 包文件名 */

} iPAK_GCA;

/*
---------------------------------------
    释放接口
---------------------------------------
*/
static void_t
iPAK_GCA_release (
  __CR_IN__ iPACKAGE*   that
    )
{
    uint_t          idx;
    iPAK_GCA*       real;
    sPAK_GCA_FILE*  list;

    pack_free_list(that);
    real = (iPAK_GCA*)that;
    list = (sPAK_GCA_FILE*)real->pack.__filelst__;
    if (list != NULL) {
        for (idx = 0; idx < real->m_cnt; idx++) {
            mem_free(list[idx].base.find);
            mem_free(list[idx].base.name);
        }
        mem_free(list);
    }
    real->m_gca->CloseArchive();
    real->m_gca->Free();
    delete real->m_gca;
    mem_free(real->m_str);
    mem_free(that);
}

/*
---------------------------------------
    扩展接口
---------------------------------------
*/
static void_t*
iPAK_GCA_getMore (
  __CR_IN__ iPACKAGE*   that,
  __CR_IN__ port_t      iid
    )
{
    /* 判断一下名称 */
    if (str_cmpA(iid, "iPACKAGE::GCA") != 0)
        return (NULL);
    return ((void_t*)that);
}

/*
---------------------------------------
    读取文件个数
---------------------------------------
*/
static int64u
iPAK_GCA_getFileNum (
  __CR_IN__ iPACKAGE*   that
    )
{
    return (((iPAK_GCA*)that)->m_cnt);
}

/*
---------------------------------------
    读取文件数据
---------------------------------------
*/
static bool_t
iPAK_GCA_getFileData (
  __CR_IN__ iPACKAGE*   that,
  __CR_OT__ sBUFFER*    buff,
  __CR_IN__ int64u      index,
  __CR_IN__ bool_t      hash
    )
{
    uint_t          idx;
    int64u          size;
    void_t*         data;
    iPAK_GCA*       real;
    sPAK_GCA_FILE*  list;

    /* 定位文件索引 */
    CR_NOUSE(hash);
    real = (iPAK_GCA*)that;
    if (index >= real->m_cnt) {
        err_set(__CR_GCAX_CPP__, index,
                "iPACKAGE::getFileData()", "index: out of bounds");
        return (FALSE);
    }
    idx = (uint_t)index;
    list = (sPAK_GCA_FILE*)real->pack.__filelst__;

    /* 获取文件数据 (0大小文件分配1个字节) */
    size = list[idx].base.size;
    if (size == 0) {
        data = mem_malloc(1);
        if (data == NULL) {
            err_set(__CR_GCAX_CPP__, CR_NULL,
                    "iPACKAGE::getFileData()", "mem_malloc() failure");
            return (FALSE);
        }
        size = 1;
        *(byte_t*)data = 0x00;
    }
    else {
        data = mem_malloc64(size);
        if (data == NULL) {
            err_set(__CR_GCAX_CPP__, CR_NULL,
                    "iPACKAGE::getFileData()", "mem_malloc64() failure");
            return (FALSE);
        }
        if (!real->m_gca->ExtractFileToMemory((int)idx, (BYTE*)data)) {
            err_set(__CR_GCAX_CPP__, FALSE,
                    "iPACKAGE::getFileData()",
                    "CGca::ExtractFileToMemory() failure");
            mem_free(data);
            return (FALSE);
        }
    }

    /* 返回文件数据 */
    return (buffer_init(buff, data, (leng_t)size, TRUE));
}

/*
---------------------------------------
    读取文件信息
---------------------------------------
*/
static bool_t
iPAK_GCA_getFileInfo (
  __CR_IN__ iPACKAGE*   that,
  __CR_OT__ sPAK_FILE** info,
  __CR_IN__ int64u      index
    )
{
    uint_t          idx;
    iPAK_GCA*       real;
    sPAK_GCA_FILE*  list;

    /* 定位文件索引 */
    real = (iPAK_GCA*)that;
    if (index >= real->m_cnt) {
        err_set(__CR_GCAX_CPP__, index,
                "iPACKAGE::getFileInfo()", "index: out of bounds");
        return (FALSE);
    }
    idx = (uint_t)index;
    list = (sPAK_GCA_FILE*)real->pack.__filelst__;

    /* 返回文件信息 */
    *info = (sPAK_FILE*)(&list[idx]);
    return (TRUE);
}

/* 接口虚函数表 */
static const iPACKAGE_vtbl _rom_ s_pack_vtbl =
{
    iPAK_GCA_release, iPAK_GCA_getMore,
    iPAK_GCA_getFileNum, iPAK_GCA_getFileData,
    iPAK_GCA_getFileInfo,

};

/*
=======================================
    GCA 文件读取
=======================================
*/
CR_API sFMT_PRT*
load_syn_gca (
  __CR_IO__ iDATIN*         datin,
  __CR_IN__ const sLOADER*  param
    )
{
    /* 只支持磁盘文件 */
    if (param->type != CR_LDR_ANSI &&
        param->type != CR_LDR_WIDE) {
        err_set(__CR_GCAX_CPP__, param->type,
                "load_syn_gca()", "invalid param: param->type");
        return (NULL);
    }

    leng_t  back;
    byte_t  tag[4];
    sLOADER loader;

    /* 预先判断一下文件类型, 不支持文件区段功能 */
    struct_cpy(&loader, param, sLOADER);
    loader.head = loader.tail = 0;
    datin = create_file_inX(&loader);
    if (datin == NULL) {
        err_set(__CR_GCAX_CPP__, CR_NULL,
                "load_syn_gca()", "create_file_inX() failure");
        return (NULL);
    }
    back = CR_VCALL(datin)->read(datin, tag, sizeof(tag));
    CR_VCALL(datin)->release(datin);
    if (back != sizeof(tag)) {
        err_set(__CR_GCAX_CPP__, back,
                "load_syn_gca()", "iDATIN::read() failure");
        return (NULL);
    }
    if (mem_cmp(tag, "GCAX", 4) != 0 &&
        mem_cmp(tag,  "MZ" , 2) != 0) {
        err_set(__CR_GCAX_CPP__, CR_ERROR,
                "load_syn_gca()", "invalid GCA format");
        return (NULL);
    }

    CGca*   gca = new CGca ();

    /* 初始化 GCA 对象 */
    if (!gca->Init()) {
        err_set(__CR_GCAX_CPP__, FALSE,
                "load_syn_gca()", "CGca::Init() failure");
        return (NULL);
    }

    ansi_t* str;

    /* 设置文件路径 */
    if (param->type == CR_LDR_ANSI) {
        str = str_dupA(param->name.ansi);
        if (str == NULL) {
            err_set(__CR_GCAX_CPP__, CR_NULL,
                    "load_syn_gca()", "str_dupA() failure");
            goto _failure1;
        }
    }
    else {
        str = utf16_to_local(CR_LOCAL, param->name.wide);
        if (str == NULL) {
            err_set(__CR_GCAX_CPP__, CR_NULL,
                    "load_syn_gca()", "utf16_to_local() failure");
            goto _failure1;
        }
    }
    gca->SetArcFilePath(str);

    bool_t  password;

    /* 设置密码 (如果有的话) */
    if (param->aprm != NULL &&
        *(byte_t*)param->aprm != 0x00) {
        password = TRUE;
        gca->SetCrypto(TRUE);
        gca->SetSpell((ansi_t*)param->aprm);
    }
    else {
        password = FALSE;
        gca->SetCrypto(FALSE);
    }

    int32u  offset = 0;

    /* 支持自解压 EXE 文件 */
    if (mem_cmp(tag, "MZ", 2) == 0) {
        offset = GetStartOffset(str);
        if (offset == 0) {
            err_set(__CR_GCAX_CPP__, offset,
                    "load_syn_gca()", "invalid GCA format");
            goto _failure2;
        }
        gca->SetStartOffset(offset);
    }

    /* 打开 GCA 压缩包 */
    if (!gca->OpenArchive()) {
        err_set(__CR_GCAX_CPP__, FALSE,
                "load_syn_gca()", "CGca::OpenArchive() failure");
        goto _failure2;
    }

    uint_t          type;
    uint_t          cnt, idx = 0;
    sPAK_GCA_FILE*  list = NULL;

    /* 加载文件信息表 */
    type = gca->GetArcType();
    cnt = gca->GetNumFiles();
    if (cnt != 0) {
        list = mem_talloc(cnt, sPAK_GCA_FILE);
        if (list == NULL) {
            err_set(__CR_GCAX_CPP__, CR_NULL,
                    "load_syn_gca()", "mem_talloc() failure");
            goto _failure3;
        }
        mem_zero(list, cnt * sizeof(sPAK_GCA_FILE));
        for (idx = 0; idx < cnt; idx++)
        {
            string  name = gca->GetFileName((int)idx);

            /* 文件名统一使用 UTF-8 编码 */
            list[idx].base.name = local_to_utf8(param->page, name.c_str());
            if (list[idx].base.name == NULL) {
                err_set(__CR_GCAX_CPP__, CR_NULL,
                        "load_syn_gca()", "local_to_utf8() failure");
                goto _failure4;
            }

            FILETIME    ftime = gca->GetFileTime((int)idx);

            /* 设置私有文件属性 */
            list[idx].crc32 = gca->GetFileCRC((int)idx);
            list[idx].fattr = gca->GetFileAttributesA((int)idx);
            list[idx].ftime = mk_size(ftime.dwHighDateTime,
                                      ftime.dwLowDateTime);
            /* 设置公用文件属性 */
            list[idx].base.skip = sizeof(sPAK_GCA_FILE);
            list[idx].base.offs = offset;   /* 这里的偏移没有实际用处 */
            list[idx].base.pack = gca->GetDataSize((int)idx);
            list[idx].base.size = gca->GetFileSize((int)idx);
            if (list[idx].base.pack != list[idx].base.size)
                list[idx].base.attr |= PAK_FILE_CMP;
            if (password)
                list[idx].base.attr |= PAK_FILE_ENC;
            if (type == CGca::GCA0)
                list[idx].base.memo = "GCA0";
            else
            if (type == CGca::GCA1)
                list[idx].base.memo = "GCA1";
        }
    }

    iPAK_GCA*   port;

    /* 生成读包接口对象 */
    port = struct_new(iPAK_GCA);
    if (port == NULL) {
        err_set(__CR_GCAX_CPP__, CR_NULL,
                "load_syn_gca()", "struct_new() failure");
        goto _failure4;
    }
    port->m_gca = gca;
    port->m_cnt = cnt;
    port->m_str = str;
    port->pack.__filelst__ = (sPAK_FILE*)list;
    port->pack.__vptr__ = &s_pack_vtbl;
    if (!pack_init_list((iPACKAGE*)port, TRUE)) {
        err_set(__CR_GCAX_CPP__, FALSE,
                "load_syn_gca()", "pack_init_list() failure");
        mem_free(port);
        goto _failure4;
    }

    sFMT_PRT*   rett;

    /* 返回读取的文件数据 */
    rett = struct_new(sFMT_PRT);
    if (rett == NULL) {
        err_set(__CR_GCAX_CPP__, CR_NULL,
                "load_syn_gca()", "struct_new() failure");
        iPAK_GCA_release((iPACKAGE*)port);
        return (NULL);
    }
    rett->type = CR_FMTZ_PRT;
    rett->port = (iPORT*)port;
    rett->more = "iPACKAGE";
    rett->infor = "G Compression Archiver (GCA)";
    return (rett);

_failure4:
    if (list != NULL) {
        for (cnt = 0; cnt < idx; cnt++) {
            TRY_FREE(list[cnt].base.find)
            mem_free(list[cnt].base.name);
        }
        mem_free(list);
    }
_failure3:
    gca->CloseArchive();
_failure2:
    mem_free(str);
_failure1:
    gca->Free();
    delete gca;
    return (NULL);
}

#endif  /* _CR_HAVE_PAK_GCA_ */

#endif  /* !__CR_GCAX_CPP__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
