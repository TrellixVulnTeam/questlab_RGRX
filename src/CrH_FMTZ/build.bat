@echo off
rem =====================
call "%VS71COMNTOOLS%vsvars32.bat"
rem =====================
nmake -fe_syn.mak
rem =====================
call "%VS100COMNTOOLS%vsvars32.bat"
rem =====================
nmake -fe_crhack.mak
rem =====================
nmake -fe_fimage.mak
rem =====================
nmake -fe_devil.mak
rem =====================
nmake -fe_fmodex.mak
rem =====================
nmake -fe_dshow.mak
rem =====================
nmake -fe_rar.mak
rem =====================
