@echo off
call "%VS100COMNTOOLS%vsvars32.bat"
nmake -fRunTcl.mak
pause
