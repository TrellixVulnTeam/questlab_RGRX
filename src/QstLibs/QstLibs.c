
#include "QstLibs.h"

#if defined(_CR_BUILD_DLL_)
/*
=======================================
    DLL 入口点
=======================================
*/
BOOL WINAPI
DllMain (
  __CR_IN__ HANDLE  hinst,
  __CR_IN__ DWORD   reason,
  __CR_UU__ LPVOID  reserved
    )
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

/* 公用查找结构 */
typedef struct
{
        /* 名称放在第一位 */
        const ansi_t*   name;

} sQST_FIND;

/*
---------------------------------------
    成员比较回调
---------------------------------------
*/
static bool_t
unit_comp (
  __CR_IN__ const void_t*   key,
  __CR_IN__ const void_t*   obj
    )
{
    sQST_FIND*  unit = (sQST_FIND*)obj;

    return (str_cmpA(unit->name, (ansi_t*)key) == 0);
}

/*
---------------------------------------
    成员索引回调
---------------------------------------
*/
static uint_t
unit_find (
  __CR_IN__ const void_t*   key
    )
{
    return (hash_str_djb2(key, str_lenA((ansi_t*)key)));
}

/*****************************************************************************/
/*                               内存共享文件                                */
/*****************************************************************************/

/*
=======================================
    创建内存共享文件
=======================================
*/
CR_API share_t STDCALL
share_file_open (
  __CR_IN__ const ansi_t*   name,
  __CR_OT__ ansi_t          strn[50],
  __CR_IN__ leng_t          size
    )
{
    int32u  crc32;
    leng_t  length;
    byte_t  hash[24];

    /* 文件大小过滤 */
    if (size < CR_K2B(4))
        size = CR_K2B(4);
    else
    if (size >= ((leng_t)-1) / 8)
        return (NULL);

    /* 直接使用名称 */
    if (strn == NULL) {
        return ((share_t)CreateFileMappingA(INVALID_HANDLE_VALUE, NULL,
            PAGE_READWRITE, (DWORD)size_hi(size), (DWORD)size, name));
    }

    /* 使用哈希过的名称 */
    length = str_lenA(name);
    crc32 = hash_crc32i_total(name, length);
    *(int32u*)(&hash[0]) = DWORD_BE(crc32);
    *(int32u*)(&hash[4]) = DWORD_BE(timer_get32());
    hash_md5_total(&hash[8], name, length);
    hex2strA(strn, hash, sizeof(hash));
    return ((share_t)CreateFileMappingA(INVALID_HANDLE_VALUE, NULL,
        PAGE_READWRITE, (DWORD)size_hi(size), (DWORD)size, strn));
}

/*
=======================================
    关闭内存共享文件
=======================================
*/
CR_API void_t STDCALL
share_file_close (
  __CR_IN__ share_t sfile
    )
{
    CloseHandle((HANDLE)sfile);
}

/*
=======================================
    填充内存共享文件
=======================================
*/
CR_API bool_t STDCALL
share_file_fill (
  __CR_IN__ share_t         sfile,
  __CR_IN__ const void_t*   data,
  __CR_IN__ leng_t          size
    )
{
    LPVOID  buff;
    HANDLE  fmap = (HANDLE)sfile;

    /* 将本地文件复制到共享内存 */
    buff = MapViewOfFile(fmap, FILE_MAP_WRITE, 0, 0, size);
    if (buff == NULL)
        return (FALSE);
    mem_cpy(buff, data, size);
    UnmapViewOfFile(buff);
    return (TRUE);
}

/*
=======================================
    获取内存共享文件
=======================================
*/
CR_API void_t* STDCALL
share_file_get (
  __CR_IN__ const ansi_t*   name,
  __CR_IN__ leng_t          size
    )
{
    LPVOID  buff;
    HANDLE  fmap;
    void_t* data;

    /* 将共享文件复制到本地内存 */
    fmap = OpenFileMappingA(FILE_MAP_READ, FALSE, name);
    if (fmap == NULL)
        return (NULL);
    buff = MapViewOfFile(fmap, FILE_MAP_READ, 0, 0, size);
    if (buff == NULL)
        goto _failure1;
    data = mem_malloc(size);
    if (data == NULL)
        goto _failure2;
    mem_cpy(data, buff, size);
    UnmapViewOfFile(buff);
    CloseHandle(fmap);
    return (data);

_failure2:
    UnmapViewOfFile(buff);
_failure1:
    CloseHandle(fmap);
    return (NULL);
}

/*
=======================================
    设置内存共享文件
=======================================
*/
CR_API bool_t STDCALL
share_file_set (
  __CR_IN__ const ansi_t*   name,
  __CR_IN__ const void_t*   data,
  __CR_IN__ leng_t          size
    )
{
    LPVOID  buff;
    HANDLE  fmap;

    /* 将本地文件复制到共享内存 */
    fmap = OpenFileMappingA(FILE_MAP_WRITE, FALSE, name);
    if (fmap == NULL)
        return (FALSE);
    buff = MapViewOfFile(fmap, FILE_MAP_WRITE, 0, 0, size);
    if (buff == NULL) {
        CloseHandle(fmap);
        return (FALSE);
    }
    mem_cpy(buff, data, size);
    UnmapViewOfFile(buff);
    CloseHandle(fmap);
    return (TRUE);
}

/*****************************************************************************/
/*                               TCP 网络通讯                                */
/*****************************************************************************/

/* 最大传输长度 */
#define QST_MAX_PACK           1024
#define QST_MAX_MESS    (QST_MAX_PACK - 2)

/*
=======================================
    TCP 网络发送字符串
=======================================
*/
CR_API bool_t STDCALL
netw_cmd_send (
  __CR_IN__ socket_t        netw,
  __CR_IN__ const ansi_t*   string
    )
{
    int16u  size;
    uint_t  back;
    byte_t  buf[QST_MAX_PACK];
    leng_t  leng = str_lenA(string);

    /* 封装发送数据 */
    if (leng > QST_MAX_MESS)
        return (FALSE);
    size = (int16u)leng;
    *(int16u*)buf = WORD_BE(size);
    mem_cpy(&buf[2], string, leng);

    /* 发送数据包 */
    leng += sizeof(int16u);
    back = socket_tcp_send(netw, buf, (uint_t)leng);
    return ((back != leng) ? FALSE : TRUE);
}

/*
=======================================
    TCP 网络接收字符串
=======================================
*/
CR_API ansi_t* STDCALL
netw_cmd_recv (
  __CR_IN__ socket_t    netw
    )
{
    int16u  size;
    uint_t  back;
    uint_t  leng;
    ansi_t* string;

    /* 先接收字符串长度 */
    back = socket_tcp_recv(netw, &size, 2);
    if (back != 2)
        return (NULL);
    leng = WORD_BE(size);
    string = str_allocA(leng + 1);
    if (string == NULL)
        return (NULL);

    /* 接收后面的字符串 */
    back = socket_tcp_recv(netw, string, leng);
    if (back != leng) {
        mem_free(string);
        return (NULL);
    }
    string[leng] = NIL;
    return (string);
}

/*
=======================================
    TCP 网络接收字符串 (服务端用)
=======================================
*/
CR_API ansi_t* STDCALL
netw_cmd_recv_ex (
  __CR_IN__ socket_t    netw
    )
{
    int16u  size;
    uint_t  back;
    uint_t  leng;
    ansi_t* string;

    /* 先接收字符串长度 */
    socket_set_timeout(netw, -1, -1);
    back = socket_tcp_recv(netw, &size, 2);
    if (back != 2)
        return (NULL);
    leng = WORD_BE(size);
    string = str_allocA(leng + 1);
    if (string == NULL)
        return (NULL);

    /* 接收后面的字符串 */
    socket_set_timeout(netw, -1, QST_TCP_TOUT);
    back = socket_tcp_recv(netw, string, leng);
    if (back != leng) {
        mem_free(string);
        return (NULL);
    }
    string[leng] = NIL;
    return (string);
}

/*
=======================================
    TCP 网络发送响应
=======================================
*/
CR_API bool_t STDCALL
netw_ack_send (
  __CR_IN__ socket_t    netw,
  __CR_IN__ bool_t      ack
    )
{
    uint_t  back;
    int32u  vals;

    if (ack)
        vals = mk_tag4("OKAY");
    else
        vals = mk_tag4("FAIL");
    back = socket_tcp_send(netw, &vals, 4);
    return ((back != 4) ? FALSE : TRUE);
}

/*
=======================================
    TCP 网络接收响应
=======================================
*/
CR_API bool_t STDCALL
netw_ack_recv (
  __CR_IN__ socket_t    netw,
  __CR_OT__ bool_t*     ack
    )
{
    uint_t  back;
    int32u  vals;

    back = socket_tcp_recv(netw, &vals, 4);
    if (back != 4)
        return (FALSE);
    if (vals == mk_tag4("OKAY"))
        *ack = TRUE;
    else
    if (vals == mk_tag4("FAIL"))
        *ack = FALSE;
    else
        return (FALSE);
    return (TRUE);
}

/*
=======================================
    TCP 网络库初始化
=======================================
*/
CR_API bool_t STDCALL
netw_cli_init (void_t)
{
    return (socket_init());
}

/*
=======================================
    TCP 网络连接到服务器
=======================================
*/
CR_API socket_t STDCALL
netw_cli_open (
  __CR_IN__ const ansi_t*   name
    )
{
    sINIu*      ini;
    bool_t      ack;
    uint_t      temp;
    int16u      port;
    ansi_t*     addr;
    ansi_t*     text;
    socket_t    netw;

    /* 读取参数 */
    port = QST_DEF_PORT;
    addr = QST_DEF_ADDR;
    text = file_load_as_strA(QST_CFG_STARTUP);
    if (text != NULL) {
        ini = ini_parseU(text);
        mem_free(text);
        text = NULL;
        if (ini != NULL) {
            text = ini_key_stringU("serv::addr", ini);
            if (text != NULL)
                addr = text;
            temp = ini_key_intxU("serv::port", QST_DEF_PORT, ini);
            if (temp > 1024 && temp < 32768)
                port = (int16u)temp;
            ini_closeU(ini);
        }
    }

    /* 创建连接 */
    netw = client_tcp_open(addr, port, -1);
    TRY_FREE(text)
    if (netw == NULL)
        return (NULL);
    socket_set_timeout(netw, -1, QST_TCP_TOUT);

    /* 发送客户端名称 */
    if (!netw_cmd_send(netw, name))
        goto _failure;
    if (!netw_ack_recv(netw, &ack) || !ack)
        goto _failure;
    socket_set_timeout(netw, -1, -1);
    return (netw);

_failure:
    socket_close(netw);
    return (NULL);
}

/*
=======================================
    TCP 网络断开连接
=======================================
*/
CR_API void_t STDCALL
netw_cli_close (
  __CR_IN__ socket_t    netw
    )
{
    /* 确保数据发送完成 */
    socket_shutdown(netw, CR_NET_SHT_TX);
    socket_close(netw);
}

/*
=======================================
    TCP 网络关闭接收
=======================================
*/
CR_API void_t STDCALL
netw_rcv_shutdwn (
  __CR_IN__ socket_t    netw
    )
{
    socket_shutdown(netw, CR_NET_SHT_RX);
}

/*
=======================================
    TCP 网络设置接收超时 (ms)
=======================================
*/
CR_API void_t STDCALL
netw_rcv_timeout (
  __CR_IN__ socket_t    netw,
  __CR_IN__ int32s      time
    )
{
    /* time 小于0表示永远 */
    socket_set_timeout(netw, -1, time);
}

/*****************************************************************************/
/*                               操作命令函数                                */
/*****************************************************************************/

/*
=======================================
    SHL 命令参数提取
=======================================
*/
CR_API ansi_t** STDCALL
cmd_shl_split (
  __CR_IO__ ansi_t* string,
  __CR_OT__ uint_t* count
    )
{
    return (str_cmd_splitA(string, count));
}

/*
=======================================
    SHL 命令参数读取
=======================================
*/
CR_API ansi_t* STDCALL
cmd_shl_param (
  __CR_IN__ ansi_t**    param,
  __CR_IN__ uint_t      index
    )
{
    return (param[index]);
}

/*
---------------------------------------
    命令数据提取
---------------------------------------
*/
static ansi_t*
cmd_data_get (
  __CR_IN__ ansi_t          type,
  __CR_IN__ const ansi_t*   string
    )
{
    if (string[0] != type)
        return (NULL);
    return (str_dupA(&string[1]));
}

/*
---------------------------------------
    命令数据合成
---------------------------------------
*/
static bool_t
cmd_data_send (
  __CR_IN__ socket_t        netw,
  __CR_IN__ ansi_t          type,
  __CR_IN__ const ansi_t*   string
    )
{
    bool_t  rett;
    leng_t  size;
    ansi_t* temp;

    size = str_lenA(string) + 1;
    temp = str_allocA(size + 1);
    if (temp == NULL)
        return (FALSE);
    temp[0] = type;
    mem_cpy(&temp[1], string, size);
    rett = netw_cmd_send(netw, temp);
    mem_free(temp);
    return (rett);
}

/*
=======================================
    INI 命令字符串提取
=======================================
*/
CR_API ansi_t* STDCALL
cmd_ini_get (
  __CR_IN__ const ansi_t*   string
    )
{
    return (cmd_data_get('#', string));
}

/*
=======================================
    INI 命令字符串合成
=======================================
*/
CR_API bool_t STDCALL
cmd_ini_send (
  __CR_IN__ socket_t        netw,
  __CR_IN__ const ansi_t*   string
    )
{
    return (cmd_data_send(netw, '#', string));
}

/*
=======================================
    XML 命令字符串提取
=======================================
*/
CR_API ansi_t* STDCALL
cmd_xml_get (
  __CR_IN__ const ansi_t*   string
    )
{
    return (cmd_data_get('@', string));
}

/*
=======================================
    XML 命令字符串合成
=======================================
*/
CR_API bool_t STDCALL
cmd_xml_send (
  __CR_IN__ socket_t        netw,
  __CR_IN__ const ansi_t*   string
    )
{
    return (cmd_data_send(netw, '@', string));
}

/*
=======================================
    SHL 命令字符串提取
=======================================
*/
CR_API ansi_t* STDCALL
cmd_shl_get (
  __CR_IN__ const ansi_t*   string
    )
{
    return (cmd_data_get('$', string));
}

/*
=======================================
    SHL 命令字符串合成
=======================================
*/
CR_API bool_t STDCALL
cmd_shl_send (
  __CR_IN__ socket_t        netw,
  __CR_IN__ const ansi_t*   string
    )
{
    return (cmd_data_send(netw, '$', string));
}

/*
=======================================
    是否为有效命令数据
=======================================
*/
CR_API bool_t STDCALL
cmd_type_okay (
  __CR_IN__ const ansi_t*   string
    )
{
    if (string[0] != '#' &&
        string[0] != '@' &&
        string[0] != '$')
        return (FALSE);
    return (TRUE);
}

/* 命令行执行对象 */
typedef struct
{
        /* 执行单元查找表 */
        sCURBEAD    table;

} sQST_SHL;

/*
=======================================
    命令行执行对象释放
=======================================
*/
CR_API void_t STDCALL
cmd_exec_free (
  __CR_IN__ exec_t  objs
    )
{
    sQST_SHL*   real;

    real = (sQST_SHL*)objs;
    curbead_freeT(&real->table, sQST_CMD);
    mem_free((void_t*)objs);
}

/*
=======================================
    命令行执行对象建立
=======================================
*/
CR_API exec_t STDCALL
cmd_exec_init (
  __CR_IN__ const sQST_CMD* list,
  __CR_IN__ leng_t          count
    )
{
    leng_t      idx;
    sQST_SHL*   rett;

    /* 建立结构 */
    rett = struct_new(sQST_SHL);
    if (rett == NULL)
        return (NULL);

    /* 初始化表 */
    if (!curbead_initT(&rett->table, sQST_CMD, 0))
        goto _failure;
    rett->table.find = unit_find;
    rett->table.comp = unit_comp;

    /* 插入表格 */
    for (idx = 0; idx < count; idx++) {
        if (curbead_insertT(&rett->table, sQST_CMD,
                list[idx].name, &list[idx]) == NULL) {
            curbead_freeT(&rett->table, sQST_CMD);
            goto _failure;
        }
    }
    return ((exec_t)rett);

_failure:
    mem_free(rett);
    return (NULL);
}

/*
=======================================
    命令行执行对象添加
=======================================
*/
CR_API bool_t STDCALL
cmd_exec_addn (
  __CR_IN__ exec_t          objs,
  __CR_IN__ const sQST_CMD* list
    )
{
    leng_t      idx;
    leng_t      cnts;
    sQST_SHL*   real;

    /* 统计个数 */
    cnts = 0;
    while (list[cnts].name != NULL &&
           list[cnts].exec != NULL)
        cnts += 1;

    /* 插入表格 */
    real = (sQST_SHL*)objs;
    for (idx = 0; idx < cnts; idx++) {
        if (curbead_insertT(&real->table, sQST_CMD,
                list[idx].name, &list[idx]) == NULL)
            return (FALSE);
    }
    return (TRUE);
}

/*
=======================================
    命令行执行对象执行
=======================================
*/
CR_API bool_t STDCALL
cmd_exec_main (
  __CR_IN__ exec_t          objs,
  __CR_IN__ void_t*         param,
  __CR_IN__ const ansi_t*   cmdz
    )
{
    bool_t      rett;
    uint_t      argc;
    ansi_t*     nstr;
    ansi_t**    argv;
    sQST_CMD*   unit;
    sQST_SHL*   real;

    /* 获取命令行 */
    nstr = cmd_shl_get(cmdz);
    if (nstr == NULL)
        return (FALSE);
    argv = cmd_shl_split(nstr, &argc);
    if (argv == NULL) {
        mem_free(nstr);
        return (FALSE);
    }

    /* 查找执行命令 */
    real = (sQST_SHL*)objs;
    unit = curbead_findT(&real->table, sQST_CMD, argv[0]);
    if (unit != NULL)
        rett = unit->exec(param, argc, argv);
    else
        rett = FALSE;
    mem_free(argv);
    mem_free(nstr);
    return (rett);
}

/*****************************************************************************/
/*                               杂项功能函数                                */
/*****************************************************************************/

/*
=======================================
    释放内存包装
=======================================
*/
CR_API void_t STDCALL
misc_mem_free (
  __CR_IN__ const void_t*   data
    )
{
    mem_free(data);
}

/*
=======================================
    检测程序是否运行
=======================================
*/
CR_API bool_t STDCALL
misc_is_running (
  __CR_IN__ const ansi_t*   name
    )
{
    HANDLE  mutex;

    mutex = CreateMutexA(NULL, FALSE, name);
    if (mutex != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
        return (TRUE);
    return (FALSE);
}

/* 空命令参数时使用 */
static ansi_t*  s_temp;

/*
=======================================
    返回命令行参数
=======================================
*/
CR_API ansi_t** STDCALL
misc_get_param (
  __CR_IN__ const ansi_t*   cmdz,
  __CR_IN__ uint_t*         count
    )
{
    ansi_t*     copy;
    ansi_t**    argv;

    /* 整个程序只调用一次
       返回的结果无需/不能释放 */
    copy = str_dupA(cmdz);
    if (copy == NULL) {
        s_temp = "";
        if (count != NULL)
           *count  = 0;
        return (&s_temp);
    }
    argv = cmd_shl_split(copy, count);
    if (argv == NULL) {
        s_temp = "";
        if (count != NULL)
           *count  = 0;
        return (&s_temp);
    }
    return (argv);
}

/*
---------------------------------------
    合成窗口配置路径
---------------------------------------
*/
static ansi_t*
misc_desk_mk_path (
  __CR_IN__ const ansi_t*   name
    )
{
    leng_t  size;
    ansi_t* full;

    /* 限定在这个目录下 */
    size  = str_lenA(name) + 1;
    size += str_lenA(QST_PATH_WINDOW);
    full = str_allocA(size);
    if (full == NULL)
        return (NULL);
    str_cpyA(full, QST_PATH_WINDOW);
    return (str_catA(full, name));
}

/*
=======================================
    保存窗口位置配置
=======================================
*/
CR_API bool_t STDCALL
misc_desk_save (
  __CR_IN__ const ansi_t*   name,
  __CR_IN__ sint_t          left,
  __CR_IN__ sint_t          top,
  __CR_IN__ uint_t          width,
  __CR_IN__ uint_t          height
    )
{
    FILE*   fp;
    ansi_t* full;

    /* 过滤参数 */
    if (((sint_t)width <= 0) ||
        ((sint_t)height <= 0))
        return (FALSE);

    /* 打开配置文件 */
    full = misc_desk_mk_path(name);
    if (full == NULL)
        return (FALSE);
    fp = fopen(full, "w");
    mem_free(full);
    if (fp == NULL)
        return (FALSE);

    /* 写入配置文件 */
    fprintf(fp, "win::left = %d\n", left);
    fprintf(fp, "win::top = %d\n", top);
    fprintf(fp, "win::width = %u\n", width);
    fprintf(fp, "win::height = %u\n", height);
    fclose(fp);
    return (TRUE);
}

/*
=======================================
    加载窗口位置配置
=======================================
*/
CR_API bool_t STDCALL
misc_desk_load (
  __CR_IN__ const ansi_t*   name,
  __CR_OT__ sint_t*         left,
  __CR_OT__ sint_t*         top,
  __CR_OT__ uint_t*         width,
  __CR_OT__ uint_t*         height
    )
{
    sINIu*  ini;
    ansi_t* text;
    ansi_t* full;
    sint_t  x1, y1;
    uint_t  ww, hh;

    /* 打开配置文件 */
    full = misc_desk_mk_path(name);
    if (full == NULL)
        return (FALSE);
    text = file_load_as_strA(full);
    mem_free(full);
    if (text == NULL)
        return (FALSE);

    /* 解析配置文件 */
    ini = ini_parseU(text);
    mem_free(text);
    if (ini == NULL)
        return (FALSE);
    x1 = ini_key_intxU("win::left", 0, ini);
    if (!ini->found)
        goto _failure;
    y1 = ini_key_intxU("win::top", 0, ini);
    if (!ini->found)
        goto _failure;
    ww = ini_key_intxU("win::width", 0, ini);
    if (!ini->found)
        goto _failure;
    hh = ini_key_intxU("win::height", 0, ini);
    if (!ini->found)
        goto _failure;
    ini_closeU(ini);

    /* 过滤参数 */
    if (((sint_t)ww <= 0) ||
        ((sint_t)hh <= 0))
        return (FALSE);

    /* 返回结果 */
    if (left   != NULL) *left   = x1;
    if (top    != NULL) *top    = y1;
    if (width  != NULL) *width  = ww;
    if (height != NULL) *height = hh;
    return (TRUE);

_failure:
    ini_closeU(ini);
    return (FALSE);
}

/*
=======================================
    初始化窗口位置配置
=======================================
*/
CR_API void_t STDCALL
misc_desk_init (
  __CR_IN__ const ansi_t*   name,
  __CR_OT__ sint_t*         left,
  __CR_OT__ sint_t*         top,
  __CR_OT__ uint_t*         width,
  __CR_OT__ uint_t*         height,
  __CR_IN__ uint_t          def_w,
  __CR_IN__ uint_t          def_h
    )
{
    RECT    full;
    sint_t  x1, y1;
    uint_t  ww, hh;
    uint_t  sw, sh;

    /* 加载窗口位置 */
    if (misc_desk_load(name, left, top, width, height))
        return;

    /* 失败, 使用默认 */
    ww = def_w; hh = def_h;
    if (SystemParametersInfo(SPI_GETWORKAREA, 0, &full, 0))
    {
        /* 取桌面大小 */
        sw = full.right - full.left;
        sh = full.bottom - full.top;
    }
    else
    {
        /* 失败, 取屏幕大小 */
        sw = GetSystemMetrics(SM_CXSCREEN);
        sh = GetSystemMetrics(SM_CYSCREEN);
    }

    /* 窗口居中放置 */
    if (sw < ww) ww = sw;
    if (sh < hh) hh = sh;
    x1 = (sint_t)((sw - ww) / 2);
    y1 = (sint_t)((sh - hh) / 2);
    misc_desk_save(name, x1, y1, ww, hh);

    /* 返回结果 */
    if (left   != NULL) *left   = x1;
    if (top    != NULL) *top    = y1;
    if (width  != NULL) *width  = ww;
    if (height != NULL) *height = hh;
}

/*
=======================================
    调用外部进程
=======================================
*/
CR_API bool_t STDCALL
misc_call_exe (
  __CR_IN__ const ansi_t*   name,
  __CR_IN__ bool_t          wait,
  __CR_IN__ bool_t          hide
    )
{
    DWORD               cf;
    ansi_t*             tt;
    STARTUPINFOA        si;
    PROCESS_INFORMATION pi;

    tt = str_dupA(name);
    if (tt == NULL)
        return (FALSE);
    mem_zero(&si, sizeof(si));
    si.cb = sizeof(STARTUPINFOA);
    cf = hide ? CREATE_NO_WINDOW : CREATE_NEW_CONSOLE;
    if (!CreateProcessA(NULL, tt, NULL, NULL, FALSE, cf,
                        NULL, NULL, &si, &pi)) {
        mem_free(tt);
        return (FALSE);
    }
    mem_free(tt);
    if (wait)
        WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return (TRUE);
}

/*
=======================================
    将窗口提到最前面
=======================================
*/
CR_API void_t STDCALL
misc_bring2top (
  __CR_IN__ hwnd_t  hwnd,
  __CR_IN__ hwnd_t  parent
    )
{
    LONG    style;

    /* 恢复窗口 */
    if (parent == NULL)
        parent = hwnd;
    if (IsIconic(parent))
        ShowWindow(parent, SW_RESTORE);
    style = GetWindowLong(hwnd, GWL_EXSTYLE);

    /* 强拉到最前面 */
    while (!SetWindowPos(hwnd, HWND_TOPMOST,
        0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE))
            thread_sleep(1);
    if (style & WS_EX_TOPMOST)
        return;
    thread_sleep(1);
    while (!SetWindowPos(hwnd, HWND_NOTOPMOST,
        0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE))
            thread_sleep(1);
}

/*
=======================================
    设置 CUI 程序窗口位置
=======================================
*/
CR_API bool_t STDCALL
misc_cui_setwin (
  __CR_IN__ hwnd_t  hwnd,
  __CR_IN__ hcui_t  hcui,
  __CR_IN__ sint_t  x,
  __CR_IN__ sint_t  y,
  __CR_IN__ uint_t  w,
  __CR_IN__ uint_t  h
    )
{
    RECT                rect;
    COORD               wwhh;
    CONSOLE_FONT_INFO   info;

    /* 先尝试设置位置 */
    if (!SetWindowPos(hwnd, HWND_TOP, (int)x, (int)y,
                 (int)w, (int)h, SWP_SHOWWINDOW))
        return (FALSE);

    /* 获取输出字体宽高 */
    if (!GetCurrentConsoleFont(hcui, FALSE, &info))
        return (FALSE);
    wwhh = GetConsoleFontSize(hcui, info.nFont);
    if (wwhh.X == 0 || wwhh.Y == 0)
        return (FALSE);

    /* 如果窗口高度超出则向小的靠拢 */
    if (!GetWindowRect(hwnd, &rect))
        return (FALSE);
    rect.right -= rect.left;
    rect.bottom -= rect.top;
    if (h == (uint_t)rect.bottom)
        return (TRUE);
    w = (uint_t)rect.right;
    if (h < (uint_t)rect.bottom)
        h = rect.bottom - wwhh.Y;
    return (SetWindowPos(hwnd, HWND_TOP, (int)x, (int)y,
                 (int)w, (int)h, SWP_SHOWWINDOW));
}
