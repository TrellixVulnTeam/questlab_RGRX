/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2009-12-15  */
/*     #######          ###    ###      [PORT]      ###  ~~~~~~~~~~~~~~~~~~  */
/*    ########          ###    ###                  ###  MODIFY: 2009-12-15  */
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
/*  >>>>>>>>>>>>>>>>>>>>>>>> CrHack 软件浮点头文件 <<<<<<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_FLOAT_H__
#define __CR_FLOAT_H__ 0xE290EEC7UL

/************************************/
/* +--------+----------+----------+ */
/* |  形式  |   指数   | 小数部分 | */
/* +--------+----------+----------+ */
/* |   零   |    零    |    零    | */
/* +--------+----------+----------+ */
/* | 非正规 |    零    |   非零   | */
/* +--------+----------+----------+ */
/* |  正规  | 1 ~ 2e-2 |   任意   | */
/* +--------+----------+----------+ */
/* |  无穷  |   2e-1   |    零    | */
/* +--------+----------+----------+ */
/* |  NaN   |   2e-1   |   非零   | */
/* +--------+----------+----------+ */
/* | V = ((-1) ^ S) * (2 ^ E) * M | */
/* +------------------------------+ */
/* |  非正规时                    | */
/* |  ~~~~~~~~                    | */
/* |  S = s; E = 1 - d; M = m     | */
/* +------------------------------+ */
/* |  当正规时                    | */
/* |  ~~~~~~~~                    | */
/* |  S = s; E = e - d; M = m + 1 | */
/* +------------------------------+ */
/************************************/

/*
************************************************
**  IEEE754 - FP16  s(1) e(5)  m(10)  d(15)
**  IEEE754 - FP32  s(1) e(8)  m(23)  d(127)
**  IEEE754 - FP64  s(1) e(11) m(52)  d(1023)
**  IEEE754 - FP80  s(1) e(15) m(64)  d(16383)
**  IEEE754 - FP128 s(1) e(15) m(112) d(16383)
************************************************
*/

typedef int16s  fp16_t;

/*****************************************************************************/
/*                               32位浮点类型                                */
/*****************************************************************************/

#ifdef  _CR_NO_FLT32_

typedef int32s  fp32_t;

#endif  /* _CR_NO_FLT32_ */

/*****************************************************************************/
/*                               64位浮点类型                                */
/*****************************************************************************/

#ifdef  _CR_NO_FLT64_

typedef int64s  fp64_t;

#endif  /* _CR_NO_FLT64_ */

#endif  /* !__CR_FLOAT_H__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
