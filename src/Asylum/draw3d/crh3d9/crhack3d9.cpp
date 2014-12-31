/*
***************************************
*   Asylum3D @ 2014-12-30
***************************************
*/

#include "../../asylum.hpp"

/*************************/
/* CrHack3D9 Main Object */
/*************************/
struct crhack3d9_main
{
    asy::crh3d9_main                main;
    asy::map_acs<asy::crh3d9_texr>  texs;
    asy::map_acs<asy::object_base>  base;
    asy::array<asy::object_inst>    inst;

    sCAMERA     cam;
    sFRUSTUM    frt;
};

/* ==================================== */
CR_API crh3d9_t crhack3d9_init (HWND hwnd)
{
    sDX9_HDLE   hdle;

#if defined(ASY_USE_STATIC)
    hdle.call = d3d9call_get();
#else
    sbin_t      sbin;
    nopfunc_t   func;

    sbin = sbin_testA("GFX3_D3D9.dll");
    if (sbin == NULL) {
        sbin = sbin_loadA("GFX3_D3D9.dll");
        if (sbin == NULL)
            return (NULL);
    }
    func = sbin_exportT(sbin, "d3d9call_get", nopfunc_t);
    if (func == NULL)
        return (NULL);
    hdle.call = (const sD3D9_CALL*)func();
#endif
    hdle.hwnd = hwnd;

    crhack3d9_main* rett;

    rett = struct_new(crhack3d9_main);
    if (rett == NULL)
        return (NULL);
    if (!rett->main.init(&hdle, 90.0f, FALSE, 0, 0, D3DFMT_UNKNOWN,
                        D3DFMT_D24X8, TRUE, D3DMULTISAMPLE_NONE)) {
        if (!rett->main.init(&hdle, 90.0f, FALSE, 0, 0, D3DFMT_UNKNOWN,
                            D3DFMT_D16, TRUE, D3DMULTISAMPLE_NONE))
            goto _failure1;
    }
    if (!rett->texs.init())
        goto _failure2;
    if (!rett->base.init())
        goto _failure3;
    rett->inst.init();
    rett->main.set_camera(&rett->cam);
    rett->main.get_frustum(&rett->frt, -1.0f);
    return ((crh3d9_t)rett);

_failure3:
    rett->texs.free();
_failure2:
    rett->main.free();
_failure1:
    mem_free(rett);
    return (NULL);
}

/* ====================================== */
CR_API void crhack3d9_kill (crh3d9_t render)
{
    crhack3d9_main* real;

    real = (crhack3d9_main*)render;
    real->inst.free();
    real->base.free();
    real->texs.free();
    real->main.free();
    mem_free(render);
}

/* ======================================= */
CR_API bool crhack3d9_reset (crh3d9_t render)
{
    crhack3d9_main* real;

    real = (crhack3d9_main*)render;
    if (!real->main.reset())
        return (false);

    size_t              num;
    asy::crh3d9_texr*   tex;

    num = real->texs.size();
    tex = real->texs.data();
    for (size_t idx = 0; idx < num; idx++) {
        if (!tex[idx].reset())
            return (false);
    }
    return (true);
}
