/*
===============================================================================
*   �����ļ�
*
*   2007-12-25  �޸ķ��
===============================================================================
*/

#ifndef _PNDR_CONF_H_
#define _PNDR_CONF_H_

/*
===============================================================================
*   ƽ̨���
===============================================================================
*/
/*
    ʹ�� WIN32 API

#define PNDR_WIN32
*/

/*
    ����״̬
    ����������Ա����ͻ���

#define PNDR_DEBUG
*/

/*
    ֧�ָ���������

#define PNDR_SUPPORT_REAL
*/

/*
    ����������������

#define PNDR_INLINE     static
#define PNDR_FASTCALL
*/
#define PNDR_INLINE     __inline
#define PNDR_FASTCALL   __fastcall

/*
===============================================================================
*   �Ƿ����� DLL
===============================================================================
*/
#ifdef  PNDR_WIN32
    #ifdef  PNDR_DLL
        #define PNDR_API    __declspec(dllexport)
    #else
        #define PNDR_API
    #endif
#else
    #define PNDR_API
#endif

/*
===============================================================================
*   ���Ͷ���
===============================================================================
*/
typedef unsigned char   byte_t;
typedef unsigned short  word_t;
typedef   signed int    sint_t;
typedef unsigned int    uint_t;
typedef unsigned long   uint32;
#ifdef  PNDR_SUPPORT_REAL
typedef float           real_t;
#endif

/*
===============================================================================
*   ״̬����ʼ״̬
===============================================================================
*/
/*
    �Ĵ���ջ��ʼ��С
*/
#define PNDR_REG_STACK      64

/*
    ���ʽջ��ʼ��С
*/
#define PNDR_EXP_STACK      64

/*
    ѭ����βջ��ʼ��С
*/
#define PNDR_LOOP_STACK     32

/*
    �ֲ��ѳ�ʼ����
*/
#define PNDR_LOCAL_HEAP     32

/*
    �ַ�����������
*/
#define PNDR_STR_LIST       512

/*
    ����Ѵ�С
*/
#define PNDR_EXE_HEAP       4096

/*
    ����������ַ���
*/
#define PNDR_MAX_NAME       32

/*
    ���õ�����������
*/
#define PNDR_MAX_PARAM      16

/*
    ȫ�ֱ����Ѵ�С
    ��ѡ��С��������б�
*/
#define PNDR_VAR_HEAP       673

/*
17
37
79
163
331
673
1361
2729
5471
10949
21911
43853
87719
175447
350899
701819
1403641
2807303
5614657
11229331
22458671
44917381
89834777
179669557
359339171
718678369
1437356741
2147483647
*/

#endif  /* _PNDR_CONF_H_ */
