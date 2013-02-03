//---------------------------------------------------------------------------

#include <vcl.h>
#include "RunWebIE.h"
#pragma hdrstop

#include "uMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
extern ansi_t*  g_html;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
    AnsiString  html;

    /* 使用系统字体 */
    this->Font->Assign(Screen->MenuFont);

    /* 切换到指定网页 */
    html  = "file://";
    html += GetCurrentDir();
    html += "/";
    html += AnsiString(g_html);
    cppWeb->Navigate(WideString(html));
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::cppWebBeforeNavigate2(TObject *Sender,
      LPDISPATCH pDisp, Variant *URL, Variant *Flags,
      Variant *TargetFrameName, Variant *PostData, Variant *Headers,
      VARIANT_BOOL *Cancel)
{
    bool_t      rett;
    ansi_t*     line;
    ansi_t*     file;
    ansi_t*     urla;
    wchar_t*    urlw;

    /* 响应超链接事件 */
    urlw = (wchar_t*)(*URL);
    urla = utf16_to_local(CR_LOCAL, urlw);
    if (urla == NULL) {
        *Cancel = TRUE;
        return;
    }

    /* 执行外部脚本文件 */
    if (chr_cmpA(urla, "quest://", 8) == 0)
    {
        /* QstCmdz 批处理脚本 */
        *Cancel = TRUE;
        file = urla + 8;
        line = str_fmtA("QstCmdz.exe \"%s\"", file);
        mem_free(urla);
        if (line == NULL)
            return;
        rett = misc_call_exe(line, FALSE, TRUE);
        mem_free(line);
        if (rett)
            this->Close();
    }
    else
    {
        /* 普通网页跳转 */
        *Cancel = FALSE;
        mem_free(urla);
    }
}
//---------------------------------------------------------------------------
