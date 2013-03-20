/*****************************************************************************/
/*                                                  ###                      */
/*       #####          ###    ###                  ###  CREATE: 2010-01-13  */
/*     #######          ###    ###      [CORE]      ###  ~~~~~~~~~~~~~~~~~~  */
/*    ########          ###    ###                  ###  MODIFY: 2013-03-20  */
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
/*  >>>>>>>>>>>>>>>>>>>>>>>> CrHack 编码解码头文件 <<<<<<<<<<<<<<<<<<<<<<<<  */
/*  =======================================================================  */
/*****************************************************************************/

#ifndef __CR_ENCLIB_H__
#define __CR_ENCLIB_H__ 0x2C121BBAUL

#include "defs.h"

/*****************************************************************************/
/*                               数据压缩解压                                */
/*****************************************************************************/

/* aPLib */
CR_API uint_t   compr_aplib (void_t *dst, uint_t dstlen,
                             const void_t *src, uint_t srclen);

CR_API uint_t   uncompr_aplib (void_t *dst, uint_t dstlen,
                               const void_t *src, uint_t srclen);
/* BZip2 */
CR_API uint_t   compr_bzip2 (void_t *dst, uint_t dstlen,
                             const void_t *src, uint_t srclen,
                             uint_t level CR_DEFAULT(9));

CR_API uint_t   uncompr_bzip2 (void_t *dst, uint_t dstlen,
                               const void_t *src, uint_t srclen);
/* PKZip */
CR_API uint_t   compr_pkzip (void_t *dst, uint_t dstlen,
                             const void_t *src, uint_t srclen,
                             uint_t level CR_DEFAULT(9));

CR_API uint_t   uncompr_pkzip (void_t *dst, uint_t dstlen,
                               const void_t *src, uint_t srclen);
/* JCALG1 */
CR_API uint_t   compr_jcalg1 (void_t *dst, uint_t dstlen,
                              const void_t *src, uint_t srclen,
                              uint_t winlen CR_DEFAULT(8192));

CR_API uint_t   uncompr_jcalg1 (void_t *dst, uint_t dstlen,
                                const void_t *src, uint_t srclen);
/* Win32 LZ32 */
CR_API leng_t   compr_lz32 (void_t *dst, leng_t dstlen,
                            const void_t *src, leng_t srclen);

CR_API leng_t   uncompr_lz32 (void_t *dst, leng_t dstlen,
                              const void_t *src, leng_t srclen);
/* LZARI */
CR_API leng_t   compr_lzari (void_t *dst, leng_t dstlen,
                             const void_t *src, leng_t srclen,
                             uint_t fill CR_DEFAULT(0));

CR_API leng_t   uncompr_lzari (void_t *dst, leng_t dstlen,
                               const void_t *src, leng_t srclen,
                               uint_t fill CR_DEFAULT(0));
/* LZHUF */
CR_API leng_t   compr_lzhuf (void_t *dst, leng_t dstlen,
                             const void_t *src, leng_t srclen,
                             uint_t fill CR_DEFAULT(0));

CR_API leng_t   uncompr_lzhuf (void_t *dst, leng_t dstlen,
                               const void_t *src, leng_t srclen,
                               uint_t fill CR_DEFAULT(0));
/* LZMA */
typedef struct
{
        uint_t  level;      /* [ 0, 1   -   9  ], default =  5   */
        uint_t  dictlen;    /* [ 0, 4KB - 128MB], default = 16MB */
        sint_t  lc;         /* [-1, 0   -   8  ], default =  3   */
        sint_t  lp;         /* [-1, 0   -   4  ], default =  0   */
        sint_t  pb;         /* [-1, 0   -   4  ], default =  2   */
        sint_t  fb;         /* [-1, 5   - 273  ], default = 32   */
        sint_t  threads;    /* [-1, 1   -   2  ], default =  2   */
        byte_t  props[5];   /*         压缩输出的额外参数        */
} sLZMA;

CR_API leng_t   compr_lzma (void_t *dst, leng_t dstlen,
                            const void_t *src, leng_t srclen,
                            sLZMA *param);

CR_API leng_t   uncompr_lzma (void_t *dst, leng_t dstlen,
                              const void_t *src, leng_t srclen,
                              const byte_t props[5]);
/* LZSS */
CR_API leng_t   compr_lzss (void_t *dst, leng_t dstlen,
                            const void_t *src, leng_t srclen,
                            uint_t fill CR_DEFAULT(0));

CR_API leng_t   uncompr_lzss (void_t *dst, leng_t dstlen,
                              const void_t *src, leng_t srclen,
                              uint_t fill CR_DEFAULT(0));
/* LZW */
CR_API leng_t   compr_lzw (void_t *dst, leng_t dstlen,
                           const void_t *src, leng_t srclen);

CR_API leng_t   uncompr_lzw (void_t *dst, leng_t dstlen,
                             const void_t *src, leng_t srclen);
/* LZO */
CR_API leng_t   compr_lzo (void_t *dst, leng_t dstlen,
                           const void_t *src, leng_t srclen);

CR_API leng_t   uncompr_lzo (void_t *dst, leng_t dstlen,
                             const void_t *src, leng_t srclen);
/* ZLib */
CR_API uint_t   compr_zlib (void_t *dst, uint_t dstlen,
                            const void_t *src, uint_t srclen,
                            uint_t level CR_DEFAULT(9));

CR_API uint_t   uncompr_zlib (void_t *dst, uint_t dstlen,
                              const void_t *src, uint_t srclen);

/*****************************************************************************/
/*                               数据加密解密                                */
/*****************************************************************************/

/* BASE16 */
CR_API leng_t   encode_base16 (void_t *dst, leng_t dstlen,
                               const void_t *src, leng_t srclen,
                               uint_t linesize CR_DEFAULT(32));

CR_API leng_t   decode_base16 (void_t *dst, leng_t dstlen,
                               const void_t *src, leng_t srclen);
/* BASE32 */
CR_API leng_t   encode_base32 (void_t *dst, leng_t dstlen,
                               const void_t *src, leng_t srclen,
                               uint_t linesize CR_DEFAULT(32));

CR_API leng_t   decode_base32 (void_t *dst, leng_t dstlen,
                               const void_t *src, leng_t srclen);
/* Z-BASE32 */
CR_API void_t   encode_zbase32 (void_t *data, leng_t size);
CR_API void_t   decode_zbase32 (void_t *data, leng_t size);

/* BASE32-CROCKFORD */
CR_API void_t   encode_base32crk (void_t *data, leng_t size);
CR_API void_t   decode_base32crk (void_t *data, leng_t size);

/* BASE32-HEX */
CR_API void_t   encode_base32hex (void_t *data, leng_t size);
CR_API void_t   decode_base32hex (void_t *data, leng_t size);

/* BASE64 */
CR_API leng_t   encode_base64 (void_t *dst, leng_t dstlen,
                               const void_t *src, leng_t srclen,
                               uint_t linesize CR_DEFAULT(32));

CR_API leng_t   decode_base64 (void_t *dst, leng_t dstlen,
                               const void_t *src, leng_t srclen);
/* BASE64-URL */
CR_API void_t   encode_base64url (void_t *data, leng_t size);
CR_API void_t   decode_base64url (void_t *data, leng_t size);

/* UUE */
CR_API leng_t   encode_uue (void_t *dst, leng_t dstlen,
                            const void_t *src, leng_t srclen);

CR_API leng_t   decode_uue (void_t *dst, leng_t dstlen,
                            const void_t *src, leng_t srclen);
/* XXE */
CR_API leng_t   encode_xxe (void_t *dst, leng_t dstlen,
                            const void_t *src, leng_t srclen);

CR_API leng_t   decode_xxe (void_t *dst, leng_t dstlen,
                            const void_t *src, leng_t srclen);

/*****************************************************************************/
/*                               数据编码转换                                */
/*****************************************************************************/

/* Code128-A */
CR_API leng_t   gen_code128a (void_t *dst, leng_t dstlen,
                              const void_t *src, leng_t srclen);
/* Code128-B */
CR_API leng_t   gen_code128b (void_t *dst, leng_t dstlen,
                              const void_t *src, leng_t srclen);
/* Code128-C */
CR_API leng_t   gen_code128c (void_t *dst, leng_t dstlen,
                              const void_t *src, leng_t srclen);

/*****************************************************************************/
/*                               数据压缩助手                                */
/*****************************************************************************/

/* RLE 数据匹配 */
CR_API leng_t   match_rle_1 (const void_t *data, leng_t size,
                             leng_t max_count);
CR_API leng_t   match_rle_2 (const void_t *data, leng_t size,
                             leng_t max_count);
CR_API leng_t   match_rle_4 (const void_t *data, leng_t size,
                             leng_t max_count);
CR_API leng_t   match_rle_x (const void_t *data, leng_t size,
                             leng_t unit, leng_t max_count);

#endif  /* !__CR_ENCLIB_H__ */

/*****************************************************************************/
/* _________________________________________________________________________ */
/* uBMAzRBoAKAHaACQD6FoAIAPqbgA/7rIA+5CM9uKw8D4Au7u7mSIJ0t18mYz0mYz9rAQZCgHc */
/* wRIZIgHZovGBXUAZg+v0GbB+gRmgcJ7BAAAisIlAwB1Av7LSHUC/s9IdQL+w0h1Av7HZkZmgf */
/* 4JLgIAdb262gPsqAh0+zP/uQB9ZYsFZYktq+L3sMi/AAK7gAKJAUtLdfq5IANXvT8BiQzfBIv */
/* FLaAAweAEmff53wb+Adjx3kQE2xwy5Io8ithkigcFgACJBN8E3sneNvwB2xyLHDkdfA2JHSyA */
/* adtAAQPdZYgHR0dNdbZfSYP5UHWr/kQEtAHNFg+Eef/DWAKgDw== |~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< */
/*****************************************************************************/
