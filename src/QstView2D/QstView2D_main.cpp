
#include "QstView2D.h"

/* 内部函数的声明 */
CR_API void_t   qst_draw_image (sQstView2D *parm);
CR_API void_t   qst_make_image (sQstView2D *parm);
CR_API void_t   qst_set_index (sQstView2D *parm, int32u index);
CR_API void_t   qst_render_data (sQstView2D *parm, sLOADER *ldrs);
CR_API void_t   qst_move_xy (sQstView2D *parm, sint_t delta_x,
                             sint_t delta_y);
/*
---------------------------------------
    FMTZ 插件释放回调
---------------------------------------
*/
static void_t
plugin_free (
  __CR_IN__ void_t* obj
    )
{
    sENGINE**   unit;

    unit = (sENGINE**)obj;
    engine_free(*unit);
}

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
  __CR_OT__ sQV2D_conf* cfgs
    )
{
    sINIu*  ini;
    ansi_t* str;

    /* 加载配置文件 */
    str = file_load_as_strA(QST_PATH_CONFIG WIN_ICONF);
    if (str == NULL)
        goto _load_defs;
    ini = ini_parseU(str);
    mem_free(str);
    if (ini == NULL)
        goto _load_defs;

    /* 读入配置参数 */
    cfgs->bkcolor = ini_key_intx32U("qv2d::bkcolor", 0x007F7F7FUL, ini);
    cfgs->is_blends = ini_key_intxU("qv2d::is_blends", TRUE, ini);
    cfgs->is_center = ini_key_intxU("qv2d::is_center", TRUE, ini);
    cfgs->use_keycolor = ini_key_intxU("qv2d::use_keycolor", TRUE, ini);
    cfgs->def_keycolor = ini_key_intx32U("qv2d::def_keycolor",
                            0x00000000UL, ini);
    ini_closeU(ini);
    return;

_load_defs:
    cfgs->bkcolor = 0x007F7F7FUL;
    cfgs->is_blends = TRUE;
    cfgs->is_center = TRUE;
    cfgs->use_keycolor = TRUE;
    cfgs->def_keycolor = 0x00000000UL;
}

/*
=======================================
    刷新前台窗口
=======================================
*/
CR_API void_t
qst_repaint_win (
  __CR_IO__ sQstView2D* parm
    )
{
    HDC         hdc;
    HBRUSH      hbr;
    int32u      clr;
    iGFX2_GDI*  draw;
    PAINTSTRUCT paint;

    /* 后台缓冲已经建立, 刷新前台区域 */
    hdc = BeginPaint(parm->hwnd, &paint);
    if (parm->draw != NULL) {
        draw = (iGFX2_GDI*)parm->draw;
        BitBlt(hdc, 0, 0, draw->__back__.position.ww,
               draw->__back__.position.hh, draw->m_back,
               0, 1, SRCCOPY);
    }
    else {
        clr = parm->cfgs.bkcolor;
        hbr = CreateSolidBrush(argb32_to_gdi(&clr));
        if (hbr != NULL) {
            FillRect(hdc, &paint.rcPaint, hbr);
            DeleteObject(hbr);
        }
    }
    EndPaint(parm->hwnd, &paint);
}

/*
=======================================
    窗口改变大小处理
=======================================
*/
CR_API bool_t
qst_resize_win (
  __CR_IO__ sQstView2D* parm
    )
{
    bool_t  rett;

    if (parm->draw == NULL)
        return (TRUE);
    _ENTER_V2D_SINGLE_
    rett = CR_VCALL(parm->draw)->reset(parm->draw);
    if (rett) {
        qst_move_xy(parm, 0, 0);
        qst_draw_image(parm);
    }
    _LEAVE_V2D_SINGLE_
    return (rett);
}

/*
---------------------------------------
    窗口是否激活
---------------------------------------
*/
static bool_t
qst_is_active_win (
  __CR_IN__ const sQstView2D*   parm
    )
{
    if (GetActiveWindow() == parm->hwnd)
        return (TRUE);
    return (FALSE);
}

/*
=======================================
    键盘按键处理
=======================================
*/
CR_API void_t
qst_do_keyboard (
  __CR_IO__ sQstView2D* parm
    )
{
    sRECT*  window;
    sint_t  step_x;
    sint_t  step_y;
    sint_t  delta_x;
    sint_t  delta_y;
    bool_t  pressed;

    /* 窗口激活才响应按键 */
    if (!qst_is_active_win(parm)) {
        thread_sleep(1);
        return;
    }
    pressed = FALSE;
    delta_x = delta_y = 0;
    if (key_input_test(VK_UP)) {
        delta_y -= 1;
        pressed = TRUE;
    }
    if (key_input_test(VK_DOWN)) {
        delta_y += 1;
        pressed = TRUE;
    }
    if (key_input_test(VK_LEFT)) {
        delta_x -= 1;
        pressed = TRUE;
    }
    if (key_input_test(VK_RIGHT)) {
        delta_x += 1;
        pressed = TRUE;
    }
    if (pressed) {
        window = &parm->draw->__back__.position;
        step_x = (sint_t)(window->ww / 200);
        step_y = (sint_t)(window->hh / 200);
        delta_x *= (step_x == 0) ? 1 : step_x;
        delta_y *= (step_y == 0) ? 1 : step_y;
        _ENTER_V2D_SINGLE_
        qst_move_xy(parm, delta_x, delta_y);
        _LEAVE_V2D_SINGLE_
    }
    else
    if (key_input_click('Z')) {
        _ENTER_V2D_SINGLE_
        parm->trans = FALSE;
        qst_draw_image(parm);
        _LEAVE_V2D_SINGLE_
    }
    else
    if (key_input_click('X')) {
        _ENTER_V2D_SINGLE_
        parm->trans = TRUE;
        qst_draw_image(parm);
        _LEAVE_V2D_SINGLE_
    }
    else
    if (key_input_test('A')) {
        if (parm->index == 0)
            return;
        _ENTER_V2D_SINGLE_
        qst_set_index(parm, parm->index - 1);
        _LEAVE_V2D_SINGLE_
        thread_sleep(50);
    }
    else
    if (key_input_test('D')) {
        _ENTER_V2D_SINGLE_
        qst_set_index(parm, parm->index + 1);
        _LEAVE_V2D_SINGLE_
        thread_sleep(50);
    }
    else {
        thread_sleep(1);
    }
}

/*
=======================================
    鼠标移动处理
=======================================
*/
CR_API void_t
qst_do_mouse (
  __CR_IO__ sQstView2D* parm,
  __CR_IN__ sint_t      m_x,
  __CR_IN__ sint_t      m_y,
  __CR_IN__ bool_t      down
    )
{
    sint_t          delta_x;
    sint_t          delta_y;
    static sint_t   pre_x = 0;
    static sint_t   pre_y = 0;

    if (!down) {
        pre_x = m_x;
        pre_y = m_y;
        return;
    }
    delta_x = pre_x - m_x;
    delta_y = pre_y - m_y;
    pre_x = m_x;
    pre_y = m_y;
    if (delta_x == 0 && delta_y == 0)
        return;
    _ENTER_V2D_SINGLE_
    qst_move_xy(parm, delta_x, delta_y);
    _LEAVE_V2D_SINGLE_
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
qst_v2d_app_exit (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    CR_NOUSE(argc);
    CR_NOUSE(argv);
    ((sQstView2D*)parm)->quit = TRUE;
    return (FALSE);
}

/*
---------------------------------------
    显示窗口位置
---------------------------------------
*/
static bool_t
qst_v2d_win_show (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sQstView2D* ctx;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    ctx = (sQstView2D*)parm;
    misc_bring2top(ctx->hwnd, NULL);
    return (TRUE);
}

/*
---------------------------------------
    保存窗口位置
---------------------------------------
*/
static bool_t
qst_v2d_win_save (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    RECT        win;
    sQstView2D* ctx;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    /* 获取窗口位置 */
    ctx = (sQstView2D*)parm;
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
qst_v2d_win_load (
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

    sQstView2D* ctx;

    /* 设置窗口位置 */
    ctx = (sQstView2D*)parm;
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
qst_v2d_cfg_load (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sQstView2D* ctx;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    _ENTER_V2D_SINGLE_
    ctx = (sQstView2D*)parm;
    qst_load_cfg(&ctx->cfgs);
    qst_make_image(ctx);
    qst_draw_image(ctx);
    _LEAVE_V2D_SINGLE_
    return (TRUE);
}

/*
---------------------------------------
    释放所有 FMTZ 插件
---------------------------------------
*/
static bool_t
qst_v2d_ext_free (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sQstView2D* ctx;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    ctx = (sQstView2D*)parm;
    array_freeT(&ctx->extz, sENGINE*);
    ctx->extz.free = plugin_free;
    return (TRUE);
}

/*
---------------------------------------
    加载一个 FMTZ 插件
---------------------------------------
*/
static bool_t
qst_v2d_ext_load (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sbin_t      dll;
    sQstView2D* ctx;

    /* 参数解析 <插件路径> */
    if (argc < 2)
        return (FALSE);

    /* 过滤已经加载的插件 */
    if (sbin_testA(argv[1]) != NULL)
        return (TRUE);
    dll = sbin_loadA(argv[1]);
    if (dll == NULL)
        return (FALSE);

    sENGINE*        port;
    engine_init_t   func;

    /* 获取引擎接口 */
    func = sbin_exportT(dll, "engine_get", engine_init_t);
    if (func == NULL)
        goto _failure;
    if ((port = func()) == NULL)
        goto _failure;
    port->sbin = dll;
    port->mask = CR_FMTZ_MASK_DAT | CR_FMTZ_MASK_PIC;

    /* 压入插件列表 */
    ctx = (sQstView2D*)parm;
    if (array_push_growT(&ctx->extz, sENGINE*, &port) == NULL) {
        engine_free(port);
        return (FALSE);
    }
    ctx->extz.free = plugin_free;
    return (TRUE);

_failure:
    sbin_unload(dll);
    return (FALSE);
}

/*
---------------------------------------
    加载一个磁盘文件
---------------------------------------
*/
static bool_t
qst_v2d_ldr_file (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    fdist_t head;
    fdist_t tail;

    /* 参数解析 <文件路径> [头偏移] [尾偏移] */
    if (argc < 2)
        return (FALSE);
    head = tail = 0;
    if (argc > 2) {
        head = str2intx64A(argv[2]);
        if (argc > 3)
            tail = str2intx64A(argv[3]);
    }

    sLOADER     ldr;
    sQstView2D* ctx = (sQstView2D*)parm;

    /* 附加参数 aprm 不设为空 */
    set_ldrA(&ldr, argv[1], "", head, tail);

    /* 渲染目标数据 */
    _ENTER_V2D_SINGLE_
    qst_render_data(ctx, &ldr);
    _LEAVE_V2D_SINGLE_

    /* 无论成功失败都返回成功 */
    return (TRUE);
}

/*
---------------------------------------
    加载一个内存文件
---------------------------------------
*/
static bool_t
qst_v2d_ldr_smem (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    leng_t  size;
    void_t* data;
    fdist_t head;
    fdist_t tail;

    /* 参数解析 <共享名称> <文件大小> <文件路径> [头偏移] [尾偏移] */
    if (argc < 4)
        return (FALSE);
    head = tail = 0;
    size = str2intx32A(argv[2]);
    if (argc > 4) {
        head = str2intx64A(argv[4]);
        if (argc > 5)
            tail = str2intx64A(argv[5]);
    }

    sLOADER     ldr;
    sQstView2D* ctx = (sQstView2D*)parm;

    /* 获取整个共享文件 */
    data = share_file_get(argv[1], size);
    if (data == NULL)
        return (FALSE);

    /* 附加参数 aprm 不设为空 */
    set_ldrA(&ldr, argv[3], "", head, tail);
    set_ldrM(&ldr, data, size, "", head, tail);

    /* 渲染目标数据 */
    _ENTER_V2D_SINGLE_
    qst_render_data(ctx, &ldr);
    _LEAVE_V2D_SINGLE_

    /* 用完后需要释放掉 */
    mem_free(data);
    return (TRUE);
}

/*
---------------------------------------
    设置图片帧号
---------------------------------------
*/
static bool_t
qst_v2d_set_now (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    int32u  idx = 0;

    /* 参数解析 [图片帧号] */
    if (argc > 1)
        idx = str2intx32A(argv[1]);
    _ENTER_V2D_SINGLE_
    ((sQstView2D*)parm)->send = FALSE;
    qst_set_index((sQstView2D*)parm, idx);
    ((sQstView2D*)parm)->send = TRUE;
    _LEAVE_V2D_SINGLE_
    return (TRUE);
}

/*
---------------------------------------
    加载命令插件 (不需要释放)
---------------------------------------
*/
static bool_t
qst_v2d_cmd_load (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sbin_t      dll;
    sQstView2D* ctx;

    /* 参数解析 <插件路径> */
    if (argc < 2)
        return (FALSE);

    /* 过滤已经加载的插件 */
    if (sbin_testA(argv[1]) != NULL)
        return (TRUE);
    dll = sbin_loadA(argv[1]);
    if (dll == NULL)
        return (FALSE);

    sQST_CMD*   list;

    /* 获取命令表接口 */
    list = sbin_exportT(dll, "qst_cmdz", sQST_CMD*);
    if (list == NULL) {
        sbin_unload(dll);
        return (FALSE);
    }

    /* 命令加入列表 */
    ctx = (sQstView2D*)parm;
    cmd_exec_addn(ctx->objs, list);
    return (TRUE);
}

/*
---------------------------------------
    显示 Alpha 通道
---------------------------------------
*/
static bool_t
qst_v2d_g2d_alpha (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    CR_NOUSE(argc);
    CR_NOUSE(argv);

    _ENTER_V2D_SINGLE_
    ((sQstView2D*)parm)->trans = TRUE;
    qst_draw_image((sQstView2D*)parm);
    _LEAVE_V2D_SINGLE_
    return (TRUE);
}

/*
---------------------------------------
    显示 Color 通道
---------------------------------------
*/
static bool_t
qst_v2d_g2d_color (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    CR_NOUSE(argc);
    CR_NOUSE(argv);

    _ENTER_V2D_SINGLE_
    ((sQstView2D*)parm)->trans = FALSE;
    qst_draw_image((sQstView2D*)parm);
    _LEAVE_V2D_SINGLE_
    return (TRUE);
}

/*
---------------------------------------
    清除当前显示的图片
---------------------------------------
*/
static bool_t
qst_v2d_g2d_clear (
  __CR_IN__ void_t*     parm,
  __CR_IN__ uint_t      argc,
  __CR_IN__ ansi_t**    argv
    )
{
    sQstView2D* ctx;

    CR_NOUSE(argc);
    CR_NOUSE(argv);

    _ENTER_V2D_SINGLE_
    ctx = (sQstView2D*)parm;
    if (ctx->fmtz != NULL) {
        fmtz_free(ctx->fmtz);
        ctx->fmtz = NULL;
    }
    if (ctx->pictz != NULL) {
        fmtz_free((sFMTZ*)ctx->pictz);
        ctx->pictz = NULL;
        ctx->slide = NULL;
    }
    qst_make_image(ctx);
    qst_draw_image(ctx);
    _LEAVE_V2D_SINGLE_
    return (TRUE);
}

/*****************************************************************************/
/*                               命令行功能表                                */
/*****************************************************************************/

static const sQST_CMD   s_cmdz[] =
{
    /***** 公用系统命令 *****/
    { "app:exit", qst_v2d_app_exit },
    { "cfg:load", qst_v2d_cfg_load },
    { "win:load", qst_v2d_win_load },
    { "win:save", qst_v2d_win_save },
    { "win:show", qst_v2d_win_show },

    /***** 公用插件命令 *****/
    { "ext:free", qst_v2d_ext_free },
    { "ext:load", qst_v2d_ext_load },

    /***** 公用加载命令 *****/
    { "ldr:file", qst_v2d_ldr_file },
    { "ldr:smem", qst_v2d_ldr_smem },

    /***** 公用序号命令 *****/
    { "idx:set_now", qst_v2d_set_now },

    /***** 通道显示命令 *****/
    { "g2d:alpha", qst_v2d_g2d_alpha },
    { "g2d:color", qst_v2d_g2d_color },
    { "g2d:clear", qst_v2d_g2d_clear },

    /***** 二维插件命令 *****/
    { "g2d:ext:free", qst_v2d_ext_free },
    { "g2d:ext:load", qst_v2d_ext_load },

    /***** 私有命令映射 *****/
    { "qv2d:app:exit", qst_v2d_app_exit },
    { "qv2d:win:show", qst_v2d_win_show },
    { "qv2d:cmd:load", qst_v2d_cmd_load },
};

/*
=======================================
    工作线程
=======================================
*/
CR_API uint_t STDCALL
qst_v2d_main (
  __CR_IN__ void_t* param
    )
{
    exec_t      obj;
    uint_t      tim;
    fp32_t      tot;
    timer_t     log;
    sQstView2D* ctx;

    /* 加载命令表 */
    obj = cmd_exec_init(s_cmdz, cntsof(s_cmdz));
    if (obj == NULL) {
        qst_v2d_app_exit(param, 0, NULL);
        return (QST_ERROR);
    }
    tim = 0;
    tot = 0.0f;
    log = timer_new();
    ctx = (sQstView2D*)param;
    ctx->objs = obj;

    /* 工作循环 */
    while (!ctx->quit)
    {
        bool_t  rett;
        fp32_t  delta;
        ansi_t* string;

        /* 接收一条命令 */
        /* 即使是出错也要继续运行 */
        string = netw_cmd_recv(ctx->netw);
        if (string == NULL) {
            tim = 0;
            tot = 0.0f;
            thread_sleep(1);
            continue;
        }

        /* 执行这条命令 */
        if (log != NULL)
            timer_set_base(log);
        rett = cmd_exec_main(obj, ctx, string);
        mem_free(string);
        if (log != NULL && rett)
        {
            ansi_t  buf[128];

            /* 有效的操作显示计数 */
            delta = timer_get_delta(log);
            tim += 1;
            tot += delta;
            if (ctx->trans)
                string = "[Alpha]";
            else if (ctx->cfgs.is_blends)
                string = "[Blend]";
            else
                string = "[Color]";
            sprintf(buf, WIN_TITLE " - last: %.3f ms / "
                        "total: %.3f ms / count: %u %s",
                            delta, tot, tim, string);
            SetWindowTextA(ctx->hwnd, buf);
        }
    }
    if (log != NULL)
        timer_del(log);
    cmd_exec_free(obj);
    return (QST_OKAY);
}
