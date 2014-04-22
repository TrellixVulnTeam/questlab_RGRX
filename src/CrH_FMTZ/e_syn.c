/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2012-09-12  */
/*     #######          ###    ###      [FMTZ]      ###  ~~~~~~~~~~~~~~~~~~  */
/*    ########          ###    ###                  ###  MODIFY: XXXX-XX-XX  */
/*    ####  ##          ###    ###                  ###  ~~~~~~~~~~~~~~~~~~  */
/*   ###       ### ###  ###    ###    ####    ####  ###   ##  +-----------+  */
/*  ####       ######## ##########  #######  ###### ###  ###  |  A NEW C  |  */
/*  ###        ######## ########## ########  ###### ### ###   | FRAMEWORK |  */
/*  ###     ## #### ### ########## ###  ### ###     ######    |  FOR ALL  |  */
/*  ####   ### ###  ### ###    ### ###  ### ###     ######    | PLATFORMS |  */
/*  ########## ###      ###    ### ######## ####### #######   |  AND ALL  |  */
/*   #######   ###      ###    ### ########  ###### ###  ###  | COMPILERS |  */
/*    #####    ###      ###    ###  #### ##   ####  ###   ##  +-----------+  */
/*  =======================================================================  */
/*  >>>>>>>>>>>>>>>>>>>>> CrHack SYN FMTZ 插件接口实现 <<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_E_SYN_C__
#define __CR_E_SYN_C__ 0x40D7F244UL

#include "fmtint.h"
#include "fmtz/syn.h"

/* 引擎常数表 */
#undef  _CR_FMTZ_WIDE_
#include "e_syn.inl"
#define _CR_FMTZ_WIDE_
#include "e_syn.inl"
#undef  _CR_FMTZ_WIDE_

/*
---------------------------------------
    文件格式加载接口
---------------------------------------
*/
static sFMTZ*
engine_syn_load (
  __CR_IN__ sENGINE*    engine,
  __CR_IO__ sLOADER*    loader
    )
{
#if defined(_CR_HAVE_PAK_GCA_)
    if (!(engine->mask & CR_FMTZ_MASK_PAK) &&
        !(engine->mask & CR_FMTZ_MASK_PIC))
        return (NULL);
#else
    if (!(engine->mask & CR_FMTZ_MASK_PIC))
        return (NULL);
#endif
    return (fmtz_find(engine, loader));
}

/*
=======================================
    获取引擎插件接口
=======================================
*/
CR_API sENGINE*
engine_syn (void_t)
{
    sENGINE*    engine;

    engine = engine_init(s_finda, s_findw, s_loada, s_loadw);
    if (engine == NULL) {
        err_set(__CR_E_SYN_C__, CR_NULL,
                "engine_syn()", "engine_init() failure");
        return (NULL);
    }
    engine->fmtz_load = engine_syn_load;
    engine->info = "SYN FMTz Engine (Done by CrHackOS)";
    return (engine);
}

#if defined(_CR_BUILD_DLL_)
/*
=======================================
    获取引擎插件接口 (同名)
=======================================
*/
CR_API sENGINE*
engine_get (void_t)
{
    return (engine_syn());
}
#endif  /* _CR_BUILD_DLL_ */

#endif  /* !__CR_E_SYN_C__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
