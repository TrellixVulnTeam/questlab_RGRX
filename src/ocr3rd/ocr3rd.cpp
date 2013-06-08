
#include "ocr3rd.h"
#pragma warning (push)
#pragma warning (disable: 4244)
#include "tess/baseapi.h"
#pragma warning (pop)
using namespace tesseract;

/* 外部库引用 */
#ifndef _CR_NO_PRAGMA_LIB_
    #pragma comment (lib, "libtesseract302.lib")
#endif

#if defined(_CR_BUILD_DLL_)
/*
=======================================
    插件 DLL 入口点
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

/*****************************************************************************/
/*                              TESSERACT-OCR                                */
/*****************************************************************************/

/*
=======================================
    建立 TESS-OCR 对象
=======================================
*/
CR_API tess_ocr_t
tess_ocr_init (
  __CR_IN__ const ansi_t*   path,
  __CR_IN__ const ansi_t*   lang
    )
{
    TessBaseAPI*    tess;

    tess = new TessBaseAPI ();
    if (tess == NULL)
        return (NULL);
    if (tess->Init(path, lang) != 0) {
        delete tess;
        return (NULL);
    }
    return ((tess_ocr_t)tess);
}

/*
=======================================
    释放 TESS-OCR 对象
=======================================
*/
CR_API void_t
tess_ocr_kill (
  __CR_IN__ tess_ocr_t  tess_ocr
    )
{
    TessBaseAPI*    tess;

    tess = (TessBaseAPI*)tess_ocr;
    delete tess;
}

/*
=======================================
    设置 TESS-OCR 参数
=======================================
*/
CR_API bool_t
tess_ocr_set_param (
  __CR_IN__ tess_ocr_t      tess_ocr,
  __CR_IN__ const ansi_t*   name,
  __CR_IN__ const ansi_t*   value
    )
{
    TessBaseAPI*    tess;

    tess = (TessBaseAPI*)tess_ocr;
    if (!tess->SetVariable(name, value))
        return (FALSE);
    return (TRUE);
}

/*
=======================================
    设置 TESS-OCR 待识别图片
=======================================
*/
CR_API bool_t
tess_ocr_set_image (
  __CR_IN__ tess_ocr_t      tess_ocr,
  __CR_IN__ const sIMAGE*   image
    )
{
    TessBaseAPI*    tess;

    /* 只支持 8/24/32 位色图片 */
    if (image->fmt != CR_INDEX8 &&
        image->fmt != CR_ARGB888 &&
        image->fmt != CR_ARGB8888)
        return (FALSE);
    tess = (TessBaseAPI*)tess_ocr;
    tess->SetImage(image->data, image->position.ww,
                   image->position.hh, image->bpc, image->bpl);
    return (TRUE);
}

/*
=======================================
    设置 TESS-OCR 图片分辨率
=======================================
*/
CR_API void_t
tess_ocr_set_ppi (
  __CR_IN__ tess_ocr_t  tess_ocr,
  __CR_IN__ uint_t      ppi
    )
{
    TessBaseAPI*    tess;

    tess = (TessBaseAPI*)tess_ocr;
    tess->SetSourceResolution(ppi);
}

/*
=======================================
    设置 TESS-OCR 图片识别区域
=======================================
*/
CR_API void_t
tess_ocr_set_rect (
  __CR_IN__ tess_ocr_t      tess_ocr,
  __CR_IN__ const sRECT*    rect
    )
{
    TessBaseAPI*    tess;

    tess = (TessBaseAPI*)tess_ocr;
    tess->SetRectangle(rect->x1, rect->y1, rect->ww, rect->hh);
}

/*
=======================================
    获取 TESS-OCR 结果文本
=======================================
*/
CR_API ansi_t*
tess_ocr_get_utf8 (
  __CR_IN__ tess_ocr_t  tess_ocr
    )
{
    TessBaseAPI*    tess;

    tess = (TessBaseAPI*)tess_ocr;
    return (tess->GetUTF8Text());
}

/*
=======================================
    释放 TESS-OCR 返回的文本
=======================================
*/
CR_API void_t
tess_ocr_str_free (
  __CR_IN__ ansi_t* string
    )
{
    delete [] string;
}
