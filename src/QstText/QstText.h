/*
 ================================================
 *      ######
 *    #########                            ##
 *   ####    ###                           ##
 *   ##       ##                           ##
 *  ##         ## ##   ##   ####     ### ######
 *  ##         ## ##   ##  ######  ##### ######
 *  ##         ## ##   ## ###  ## ###      ##
 *  ##    #    ## ##   ## ##  ##  #####    ##
 *   ##   ##   ## ##   ## ## ##    #####   ##
 *   ###   ## ##  ##   ## ###   #     ##   ##
 *    ##########  ####### ####### ######   ##
 *      #### ##    ######   ####   ####    ##
 *            ##
 *             ##       CREATE: 2013-03-08
 *              #
 ================================================
        QuestLAB 文本浏览器
 ================================================
 */

#ifndef __QL_QSTTEXT_H__
#define __QL_QSTTEXT_H__

#include "../QstLibs/QstLibs.h"

/* 公用定义宏 */
#ifndef EXE_XNAME
    #define EXE_XNAME   "QstText"
    #define WIN_TITLE   "QstText"
    #define WIN_CLASS   "QstTextCLSS"
    #define WIN_ICONF   "QstText.ini"
    #define WIN_XCONF   "QstText.xml"
#endif

/* 配置参数结构 */
typedef struct
{
        sint_t  font_size;  /* 全局字体大小 */
        ansi_t* font_face;  /* 全局字体名称 */
        fsize_t max_fsize;  /* 最大文件大小 */

} sQEDT_conf;

/* 工作上下文结构 */
typedef struct
{
        /* 应用程序参数 */
        bool_t      quit;   /* 是否退出 */
        void_t*     form;   /* 窗口对象 */
        crsc_t      lock;   /* 同步的锁 */
        sARRAY      extz;   /* 插件列表 */
        uint_t      defs;   /* 默认编码 */
        socket_t    netw;   /* 网络连接 */
        sQEDT_conf  cfgs;   /* 配置参数 */

        /* 保存的原始文本 */
        bool_t      xbom;   /* 是否带 BOM 头 */
        uint_t      page;   /* 原始编码类型值 */
        ansi_t*     show;   /* 赋值给编辑器的指针 (不释放) */
        ansi_t*     text;   /* UNICODE 统一使用 UTF-8 保存 */

        /* 扩展名过滤列表 */
        leng_t      count;
        ansi_t*     filter;
        ansi_t**    flists;

} sQstText;

#endif  /* !__QL_QSTTEXT_H__ */
