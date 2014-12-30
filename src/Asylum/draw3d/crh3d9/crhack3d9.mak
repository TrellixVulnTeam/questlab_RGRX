PROJECT=CrHack3D9
SUBSYSTEM=WINDOWS
BIN_NAME=$(PROJECT).dll
!INCLUDE "../vc2010_x86.mak"

OBJ_LIST=.$(L)asylum.$(O) \
         .$(L)crh3d9_ff_stuff.$(O) \
         .$(L)crh3d9_wf_stuff.$(O)

SRC_LIST=.$(L)asylum.$(P) \
         .$(L)draw3d$(L)crh3d9$(L)crh3d9_ff_stuff.$(P) \
         .$(L)draw3d$(L)crh3d9$(L)crh3d9_wf_stuff.$(P)

build_all:
    $(CC) $(CFLAGS) /D "_CR_BUILD_DLL_" /D "ASY_USE_DX9" $(SRC_LIST)
    $(LD) $(LFLAGS) /DLL $(OBJ_LIST)
    $(MT) $(MFLAGS)
    move $(BIN_NAME) ..$(L)..$(L)bin$(L)
    move $(PROJECT).lib ..$(L)..$(L)tmp$(L)
    del /Q *.obj
    del /Q 2.manifest
    del /Q $(PROJECT).exp
