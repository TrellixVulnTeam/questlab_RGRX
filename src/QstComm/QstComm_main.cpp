
#include "QstCommInt.h"

/* 一些超时参数 */
#define QCOM_CUTDOWN    10      /* 断流超时 */
#define QCOM_SNDTOUT    1000    /* 发送超时 */
#define QCOM_CNNTOUT    5000    /* 连接超时 */
static uint_t   s_tout_cutdown = QCOM_CUTDOWN;
static uint_t   s_tout_connect = QCOM_CNNTOUT;

/* 内部函数的声明 */
CR_API void_t   qst_csi_clear (void_t);

/* 接收线程的声明 */
CR_API uint_t STDCALL qst_rs232_main (void_t *parm);
CR_API uint_t STDCALL qst_tcpv4_main (void_t *parm);
CR_API uint_t STDCALL qst_udpv4_main (void_t *parm);

/* 发送函数的声明 */
CR_API void_t   qst_rs232_send (void_t *obj, const void_t *data, uint_t size);
CR_API void_t   qst_tcpv4_send (void_t *obj, const void_t *data, uint_t size);
CR_API void_t   qst_udpv4_send (void_t *obj, const void_t *data, uint_t size);

/* 数据变换的声明 */
CR_API void_t*  qst_dos_tran (const ansi_t *string, uint_t *ot_size);
CR_API void_t*  qst_unx_tran (const ansi_t *string, uint_t *ot_size);
CR_API void_t*  qst_mac_tran (const ansi_t *string, uint_t *ot_size);
CR_API void_t*  qst_hex_tran (const ansi_t *string, uint_t *ot_size);
CR_API void_t*  qst_esc_tran (const ansi_t *string, uint_t *ot_size);

/* 数据渲染的声明 */
CR_API void_t   qst_htm_show (void_t *parm, const void_t *data, uint_t size);
CR_API void_t   qst_hex_show (void_t *parm, const void_t *data, uint_t size);
CR_API void_t   qst_csi_show (void_t *parm, const void_t *data, uint_t size);

/*****************************************************************************/
/*                                 内部函数                                  */
/*****************************************************************************/

/*
=======================================
    读入配置文件
=======================================
*/
CR_API void_t
qst_load_cfg (
  __CR_OT__ sQCOM_conf* cfgs
    )
{
    sINIu*  ini;
    ansi_t* str;

    /* 加载配置文件 */
    TRY_FREE(cfgs->font_face);
    str = file_load_as_strA(QST_PATH_CONFIG WIN_ICONF);
    if (str == NULL)
        goto _load_defs;
    ini = ini_parseU(str);
    mem_free(str);
    if (ini == NULL)
        goto _load_defs;

    /* 读入配置参数 */
    cfgs->color = ini_key_intx32U("qcom::color", 0xFFC0C0C0UL, ini);
    cfgs->bkcolor = ini_key_intx32U("qcom::bkcolor", 0xFF000000UL, ini);
    cfgs->font_size = ini_key_intxU("qcom::font_size", 12, ini);
    cfgs->font_face = ini_key_stringU("qcom::font_face", ini);
    ini_closeU(ini);
    return;

_load_defs:
    cfgs->color = 0xFFC0C0C0UL;
    cfgs->bkcolor = 0xFF000000UL;
    cfgs->font_size = 12;
    cfgs->font_face = NULL;
}

/*
=======================================
    刷新浏览器设置
=======================================
*/
CR_API void_t
qst_set_viewer (
  __CR_IO__ sQstComm*   parm
    )
{
    CTextOper*  opr;
    sQCOM_conf* cfg = &parm->cfgs;

    /* 设置全局字体 (默认 Consolas 字体) */
    QFont   font("Consolas", 12, QFont::Normal, false);

    if (cfg->font_face != NULL)
        font.setFamily(cfg->font_face);
    font.setPointSize(cfg->font_size);

    ansi_t  tmp[64];

    /* 设置默认前景和背景颜色
       使用 CSS 不会改变已有 HTML 文字的属性 */
    opr = (CTextOper*)parm->oper;
    cfg->color   &= 0x00FFFFFFUL;
    cfg->bkcolor &= 0x00FFFFFFUL;
    sprintf(tmp, "background-color:#%06X;color:#%06X;",
                  cfg->bkcolor, cfg->color);
    _ENTER_COM_SINGLE_
    opr->setup(font, tmp);
    sprintf(cfg->fg, "#%06X;", cfg->color);
    sprintf(cfg->bg, "#%06X;", cfg->bkcolor);
    _LEAVE_COM_SINGLE_
}

/*
=======================================
    更新窗口标题
=======================================
*/
CR_API void_t
qst_update_title (
  __CR_IN__ const sQstComm* parm
    )
{
    ansi_t*         wntt;
    const ansi_t*   type;

    if (parm->comm.title == NULL)
        type = "";
    else
        type = parm->comm.title;
    wntt = str_fmtA(WIN_TITLE "%s {s:%s, r:%s}", type,
                parm->comm.stype, parm->comm.rtype);
    if (wntt != NULL) {
        SetWindowTextA(parm->hwnd, wntt);
        mem_free(wntt);
    }
}

/*
=======================================
    文本模式去除多余换行符
=======================================
*/
CR_API uint_t
qst_txt_mode (
  __CR_IO__ ansi_t* text,
  __CR_IN__ uint_t  size
    )
{
    ansi_t  *ptr;
    uint_t  ii, jj;

    if (size < 2)
        return (size);
    size -= 1;
    ptr = text;
    for (jj = ii = 0; ii < size; ii++) {
        ptr[jj++] = text[ii];
        if (text[ii] == CR_AC('\r') && text[ii + 1] == CR_AC('\n'))
            ii++;
    }
    if (ii == size)
        ptr[jj++] = text[ii];
    return (jj);
}

/*****************************************************************************/
/*                               公用命令单元                                */
/*****************************************************************************/

/*
---------------------------------------
    退出应用程序
---------------------------------------
*/
static bool_t
qst_com_app_exit (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sQstComm*   ctx;
    CTextOper*  opr;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    ctx = (sQstComm*)parm;
    opr = (CTextOper*)ctx->oper;

    ctx->quit = TRUE;
    _ENTER_COM_SINGLE_
    opr->exit();
    _LEAVE_COM_SINGLE_
    return (FALSE);
}

/*
---------------------------------------
    显示窗口位置
---------------------------------------
*/
static bool_t
qst_com_win_show (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sQstComm*   ctx;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    ctx = (sQstComm*)parm;
    misc_bring2top(ctx->hwnd, NULL);
    return (TRUE);
}

/*
---------------------------------------
    保存窗口位置
---------------------------------------
*/
static bool_t
qst_com_win_save (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    RECT        win;
    sQstComm*   ctx;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    /* 获取窗口位置 */
    ctx = (sQstComm*)parm;
    if (!GetWindowRect(ctx->hwnd, &win))
        return (FALSE);

    sint_t  x1 = win.left;
    sint_t  y1 = win.top;
    uint_t  ww = win.right - win.left;
    uint_t  hh = win.bottom - win.top;

    /* 保存窗口位置 */
    return (misc_desk_save(WIN_ICONF, x1, y1, ww, hh));
}

/*
---------------------------------------
    加载窗口位置
---------------------------------------
*/
static bool_t
qst_com_win_load (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sint_t  x1, y1;
    uint_t  ww, hh;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    /* 保存窗口位置 */
    if (!misc_desk_load(WIN_ICONF, &x1, &y1, &ww, &hh))
        return (FALSE);

    sQstComm*   ctx;

    /* 设置窗口位置 */
    ctx = (sQstComm*)parm;
    misc_bring2top(ctx->hwnd, NULL);
    return (SetWindowPos(ctx->hwnd, HWND_TOP, (int)x1, (int)y1,
                 (int)ww, (int)hh, SWP_SHOWWINDOW));
}

/*
---------------------------------------
    加载配置文件
---------------------------------------
*/
static bool_t
qst_com_cfg_load (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sQstComm*   ctx;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    ctx = (sQstComm*)parm;
    qst_load_cfg(&ctx->cfgs);
    qst_set_viewer(ctx);
    return (TRUE);
}

/*
---------------------------------------
    清除通讯内容
---------------------------------------
*/
static bool_t
qst_com_clear (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sQstComm*   ctx;
    CTextOper*  opr;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    ctx = (sQstComm*)parm;
    opr = (CTextOper*)ctx->oper;

    _ENTER_COM_SINGLE_
    opr->clear();
    _LEAVE_COM_SINGLE_
    return (TRUE);
}

/*
---------------------------------------
    关闭通讯接口
---------------------------------------
*/
static bool_t
qst_com_close (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sQstComm*   ctx;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    ctx = (sQstComm*)parm;
    if (ctx->comm.thrd == NULL)
        return (FALSE);
    ctx->comm.quit = TRUE;
    thread_wait(ctx->comm.thrd);
    thread_del(ctx->comm.thrd);
    ctx->comm.thrd = NULL;
    ctx->comm.quit = FALSE;
    SAFE_FREE(ctx->comm.title);
    qst_update_title(ctx);
    CR_VCALL(ctx->bufs)->reput(ctx->bufs, 0);
    ctx->size = 0;
    return (TRUE);
}

/*
---------------------------------------
    打开 RS232 通讯接口
---------------------------------------
*/
static bool_t
qst_com_rs232 (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    int32u  baud;
    uint_t  port, bits;
    uint_t  stop, parity;
    /* --------------- */
    const ansi_t*   sstop;
    const ansi_t*   sparity;

    /* 参数解析 <串口号> [波特率] [数据位] [校验位] [停止位] */
    if (argc < 2)
        return (FALSE);
    bits = 8;
    baud = 115200UL;
    stop = CR_SIO_STOP10;
    parity = CR_SIO_NOP;
    sstop = "1";
    sparity = "no";
    port = str2intxA(argv[1]);
    if (argc > 2) {
        baud = str2intx32A(argv[2]);
        if (argc > 3) {
            bits = str2intxA(argv[3]);
            if (argc > 4) {
                sparity = argv[4];
                if (str_cmpA(argv[4], "no") == 0)
                    parity = CR_SIO_NOP;
                else
                if (str_cmpA(argv[4], "odd") == 0)
                    parity = CR_SIO_ODD;
                else
                if (str_cmpA(argv[4], "even") == 0)
                    parity = CR_SIO_EVEN;
                else
                if (str_cmpA(argv[4], "mark") == 0)
                    parity = CR_SIO_MARK;
                else
                if (str_cmpA(argv[4], "space") == 0)
                    parity = CR_SIO_SPCE;
                else
                    sparity = "no";
                if (argc > 5) {
                    sstop = argv[5];
                    if (str_cmpA(argv[5], "1") == 0)
                        stop = CR_SIO_STOP10;
                    else
                    if (str_cmpA(argv[5], "1.5") == 0)
                        stop = CR_SIO_STOP15;
                    else
                    if (str_cmpA(argv[5], "2") == 0)
                        stop = CR_SIO_STOP20;
                    else
                        sstop = "1";
                }
            }
        }
    }

    sQstComm*   ctx = (sQstComm*)parm;

    /* 关闭当前接口并打开串口 */
    if (!sio_open(port))
        return (FALSE);
    sio_setup(port, baud, bits, parity, stop);
    sio_set_buffer(port, CR_M2B(1), CR_K2B(1));
    sio_set_rd_timeout(port, 0, 0, s_tout_cutdown);
    sio_set_wr_timeout(port, 0, QCOM_SNDTOUT);
    sio_clear_error(port);
    sio_flush(port, CR_SIO_FLU_RT);

    /* 设置工作参数 */
    qst_com_close(parm, argc, argv);
    ctx->comm.obj.port = port;
    ctx->comm.send = qst_rs232_send;

    /* 启动接收线程 */
    ctx->comm.thrd = thread_new(0, qst_rs232_main, parm, FALSE);
    if (ctx->comm.thrd == NULL) {
        sio_close(port);
        return (FALSE);
    }
    TRY_FREE(ctx->comm.title);
    ctx->comm.title = str_fmtA(" - COM%u, %u, %u, %s, %s",
                            port, baud, bits, sparity, sstop);
    qst_update_title(ctx);
    return (TRUE);
}

/*
---------------------------------------
    打开 TCPv4 通讯接口
---------------------------------------
*/
static bool_t
qst_com_tcpv4 (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    uint_t      port;
    socket_t    netw;

    /* 参数解析 <目标地址> <端口号> */
    if (argc < 3)
        return (FALSE);
    port = str2intxA(argv[2]);
    if (port > 65535)
        return (FALSE);

    sQstComm*   ctx = (sQstComm*)parm;

    /* 关闭当前接口并打开 TCPv4 连接 */
    netw = client_tcp_open(argv[1], (int16u)port, s_tout_connect);
    if (netw == NULL)
        return (FALSE);
    socket_set_timeout(netw, QCOM_SNDTOUT, s_tout_cutdown);

    /* 设置工作参数 */
    qst_com_close(parm, argc, argv);
    ctx->comm.obj.netw = netw;
    ctx->comm.send = qst_tcpv4_send;

    /* 启动接收线程 */
    ctx->comm.thrd = thread_new(0, qst_tcpv4_main, parm, FALSE);
    if (ctx->comm.thrd == NULL) {
        socket_close(netw);
        return (FALSE);
    }
    TRY_FREE(ctx->comm.title);
    ctx->comm.title = str_fmtA(" - TCPv4 \"%s\", %u", argv[1], port);
    qst_update_title(ctx);
    return (TRUE);
}

/*
---------------------------------------
    打开 UDPv4 通讯接口
---------------------------------------
*/
static bool_t
qst_com_udpv4 (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    uint_t      port;
    socket_t    netw;

    /* 参数解析 <目标地址> <端口号> */
    if (argc < 3)
        return (FALSE);
    port = str2intxA(argv[2]);
    if (port > 65535)
        return (FALSE);

    sQstComm*   ctx = (sQstComm*)parm;

    /* 关闭当前接口并打开 UDPv4 连接 */
    netw = client_udp_open(argv[1], (int16u)port);
    if (netw == NULL)
        return (FALSE);
    socket_set_timeout(netw, QCOM_SNDTOUT, s_tout_cutdown);

    /* 设置工作参数 */
    qst_com_close(parm, argc, argv);
    ctx->comm.obj.netw = netw;
    ctx->comm.send = qst_udpv4_send;

    /* 启动接收线程 */
    ctx->comm.thrd = thread_new(0, qst_udpv4_main, parm, FALSE);
    if (ctx->comm.thrd == NULL) {
        socket_close(netw);
        return (FALSE);
    }
    TRY_FREE(ctx->comm.title);
    ctx->comm.title = str_fmtA(" - UDPv4 \"%s\", %u", argv[1], port);
    qst_update_title(ctx);
    return (TRUE);
}

/*
---------------------------------------
    设置通讯发送模式
---------------------------------------
*/
static bool_t
qst_com_stype (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    static ansi_t*  name = NULL;

    /* 参数解析 <发送模式/插件名称> [函数名称] */
    if (argc < 2)
        return (FALSE);

    sQstComm*   ctx = (sQstComm*)parm;

    if (str_cmpA(argv[1], "text") == 0) {
        ctx->comm.tran = NULL;
        ctx->comm.stype = "text";
    }
    else
    if (str_cmpA(argv[1], "hex") == 0) {
        ctx->comm.tran = qst_hex_tran;
        ctx->comm.stype = "hex";
    }
    else
    if (str_cmpA(argv[1], "esc") == 0) {
        ctx->comm.tran = qst_esc_tran;
        ctx->comm.stype = "esc";
    }
    else
    if (str_cmpA(argv[1], "dos") == 0) {
        ctx->comm.tran = qst_dos_tran;
        ctx->comm.stype = "dos";
    }
    else
    if (str_cmpA(argv[1], "unix") == 0) {
        ctx->comm.tran = qst_unx_tran;
        ctx->comm.stype = "unix";
    }
    else
    if (str_cmpA(argv[1], "mac") == 0) {
        ctx->comm.tran = qst_mac_tran;
        ctx->comm.stype = "mac";
    }
    else
    {
        sbin_t          sbin;
        plugin_tran_t   func;

        /* 使用外部插件 */
        if (argc < 3)
            return (FALSE);
        sbin = sbin_loadA(argv[1]);
        if (sbin == NULL)
            return (FALSE);
        func = sbin_exportT(sbin, argv[2], plugin_tran_t);
        if (func == NULL) {
            sbin_unload(sbin);
            return (FALSE);
        }
        ctx->comm.tran = func;
        TRY_FREE(name);
        name = str_fmtA("%s->%s", argv[1], argv[2]);
        ctx->comm.stype = (name == NULL) ? "null" : name;
    }
    qst_update_title(ctx);
    return (TRUE);
}

/*
---------------------------------------
    设置通讯接收模式
---------------------------------------
*/
static bool_t
qst_com_rtype (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    static ansi_t*  name = NULL;

    /* 参数解析 <接收模式/插件名称> [函数名称] */
    if (argc < 2)
        return (FALSE);

    sQstComm*   ctx = (sQstComm*)parm;
    CTextOper*  opr = (CTextOper*)ctx->oper;

    _ENTER_COM_SINGLE_
    if (str_cmpA(argv[1], "text") == 0) {
        ctx->comm.text = TRUE;
        ctx->comm.render = qst_txt_show;
        ctx->comm.rtype = "text";
    }
    else
    if (str_cmpA(argv[1], "html") == 0) {
        ctx->comm.text = TRUE;
        ctx->comm.render = qst_htm_show;
        ctx->comm.rtype = "html";
    }
    else
    if (str_cmpA(argv[1], "hex") == 0) {
        ctx->comm.text = FALSE;
        ctx->comm.render = qst_hex_show;
        ctx->comm.rtype = "hex";
    }
    else
    if (str_cmpA(argv[1], "ansi") == 0) {
        qst_csi_clear();
        ctx->comm.text = TRUE;
        ctx->comm.render = qst_csi_show;
        ctx->comm.rtype = "ansi";
    }
    else
    {
        sbin_t          sbin;
        plugin_render_t func;

        /* 使用外部插件 */
        if (argc < 3)
            goto _failure;
        sbin = sbin_loadA(argv[1]);
        if (sbin == NULL)
            goto _failure;
        func = sbin_exportT(sbin, argv[2], plugin_render_t);
        if (func == NULL) {
            sbin_unload(sbin);
            goto _failure;
        }
        ctx->comm.text = FALSE;
        ctx->comm.render = func;
        TRY_FREE(name);
        name = str_fmtA("%s->%s", argv[1], argv[2]);
        ctx->comm.rtype = (name == NULL) ? "null" : name;
    }
    opr->clear();
    _LEAVE_COM_SINGLE_
    qst_update_title(ctx);
    return (TRUE);

_failure:
    _LEAVE_COM_SINGLE_
    return (FALSE);
}

/*
---------------------------------------
    设置显示文本编码
---------------------------------------
*/
static bool_t
qst_com_cpage (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    uint_t  page;

    /* 参数解析 <编码> */
    if (argc < 2)
        return (FALSE);
    page = str2intxA(argv[1]);
    if (page == CR_LOCAL)
        page = get_sys_codepage();
    else
    if (is_cr_widechar(page))
        page = CR_UTF8;
    ((sQstComm*)parm)->page = page;
    return (TRUE);
}

/*
---------------------------------------
    设置两个超时时间
---------------------------------------
*/
static bool_t
qst_com_tmout (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sint_t  ctdwn, cnntt;

    /* 参数解析 <断流超时> [连接超时] */
    if (argc < 2)
        return (FALSE);
    ctdwn = str2intxA(argv[1]);
    if (ctdwn >= 0)
        s_tout_cutdown = ctdwn;
    if (argc > 2) {
        cnntt = str2intxA(argv[2]);
        if (cnntt >= 0)
            s_tout_connect = cnntt;
    }
    CR_NOUSE(parm);
    return (TRUE);
}

/*
---------------------------------------
    设置通讯断流大小
---------------------------------------
*/
static bool_t
qst_com_flush (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    /* 参数解析 <断流大小> */
    if (argc < 2)
        return (FALSE);
    ((sQstComm*)parm)->sbyt = str2intxA(argv[1]);
    return (TRUE);
}

/*****************************************************************************/
/*                               命令行功能表                                */
/*****************************************************************************/

static const sQST_CMD   s_cmdz[] =
{
    /***** 公用系统命令 *****/
    { "app:exit", qst_com_app_exit },
    { "cfg:load", qst_com_cfg_load },
    { "win:load", qst_com_win_load },
    { "win:save", qst_com_win_save },
    { "win:show", qst_com_win_show },

    /***** 通讯控制命令 *****/
    { "com:clear", qst_com_clear },
    { "com:close", qst_com_close },
    { "com:rs232", qst_com_rs232 },
    { "com:tcpv4", qst_com_tcpv4 },
    { "com:udpv4", qst_com_udpv4 },
    { "com:stype", qst_com_stype },
    { "com:rtype", qst_com_rtype },
    { "com:cpage", qst_com_cpage },
    { "com:tmout", qst_com_tmout },
    { "com:flush", qst_com_flush },

    /***** 私有命令映射 *****/
    { "qcom:app:exit", qst_com_app_exit },
    { "qcom:win:show", qst_com_win_show },
};

/*
=======================================
    工作线程
=======================================
*/
CR_API uint_t STDCALL
qst_com_main (
  __CR_IN__ void_t* param
    )
{
    exec_t      obj;
    sQstComm*   ctx;

    /* 加载命令表 */
    obj = cmd_exec_init(s_cmdz, cntsof(s_cmdz));
    if (obj == NULL) {
        qst_com_app_exit(param, 0, NULL);
        return (QST_ERROR);
    }
    ctx = (sQstComm*)param;

    /* 工作循环 */
    while (!ctx->quit)
    {
        ansi_t* string;

        /* 主动清屏 */
        if (key_input_test(VK_ESCAPE))
            qst_com_clear(param, 0, NULL);

        /* 接收一条命令 */
        /* 即使是出错也要继续运行 */
        string = netw_cmd_recv(ctx->netw);
        if (string == NULL) {
            thread_sleep(1);
            continue;
        }

        /* 非命令直接交由发送函数处理 */
        if (!cmd_type_okay(string) && ctx->comm.thrd != NULL)
        {
            if (ctx->comm.send != NULL)
            {
                if (ctx->comm.tran == NULL)
                {
                    /* 直接发送 */
                    ctx->comm.send(ctx->comm.obj.parm, string,
                                   str_lenA(string));
                }
                else
                {
                    uint_t  size;
                    void_t* send;

                    /* 变换后发送 */
                    send = ctx->comm.tran(string, &size);
                    if (send != NULL) {
                        ctx->comm.send(ctx->comm.obj.parm, send, size);
                        mem_free(send);
                    }
                }
            }
            mem_free(string);
            continue;
        }

        /* 执行这条命令 */
        cmd_exec_main(obj, ctx, string);
        mem_free(string);
    }

    /* 等待通讯线程结束 */
    if (ctx->comm.thrd != NULL) {
        ctx->comm.quit = TRUE;
        thread_wait(ctx->comm.thrd);
        thread_del(ctx->comm.thrd);
    }
    cmd_exec_free(obj);
    return (QST_OKAY);
}
