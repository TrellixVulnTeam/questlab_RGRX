PROJECT=CrH_FMTZ
SUBSYSTEM=WINDOWS
BIN_NAME=$(PROJECT).dll
!INCLUDE "../vc2010_x86.mak"

OBJ_LIST=.$(L)fmtz.$(O) \
         .$(L)cr_bmp.$(O) \
         .$(L)cr_png.$(O) \
         .$(L)cr_zip.$(O) \
         .$(L)e_crhack.$(O) \
         .$(L)$(PROJECT).res

SRC_LIST=.$(L)fmtz.$(C) \
         .$(L)cr_bmp.$(C) \
         .$(L)cr_png.$(C) \
         .$(L)cr_zip.$(C) \
         .$(L)e_crhack.$(C)

build_all:
    $(RC) $(RFLAGS)
    $(CC) $(CFLAGS) /D "_CR_BUILD_DLL_" $(SRC_LIST)
    $(LD) $(LFLAGS) /DLL $(OBJ_LIST)
    $(MT) $(MFLAGS)
    move $(BIN_NAME) ..$(L)..$(L)bin$(L)
    del /Q *.obj
    del /Q *.res
    del /Q 2.manifest
    del /Q $(PROJECT).exp
    del /Q $(PROJECT).lib
