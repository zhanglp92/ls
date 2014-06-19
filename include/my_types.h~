/*************************************************************************
	> File Name: my_types.h
	> Author: zhanglp
	> Mail: zhanglp92.gmail.com 
	> Blog: http://blog.csdn.net/zhanglpql 
	> Git: http://github.com/zhanglp92 
	> Created Time: 2014年05月17日 星期六 22时12分14秒
 ************************************************************************/

#ifndef _MY_TYPES_H_
#define _MY_TYPES_H_

#define FAIL    -1
#define SUCESS  1

/* 该ls 所能识别的参数 */
#define ARGS        "lauR"

#include <dirent.h>
// #define DT_UNKNOWN  0


/* 参数中所含有的文件的最大数目 */
#define PATH_BITS   1024

/******************************************
* 第1,2,3,4位分别表示参数 l,a,u,R 的有无
* 最低位为第1位，1表示有对应的参数，0无
*******************************************/
unsigned    _argc;

/* 得到对应参数的状态 */
#define GET_L_STAT() \
    (_argc & 0x01)

#define GET_A_STAT() \
    (_argc & 0x02)

#define GET_U_STAT() \
    (_argc & 0x04)

#define GET_R_STAT() \
    (_argc & 0x08)


#define PATH_LEN    PATH_BITS
struct _name {

    char val[PATH_LEN];
    /* 表示文件的类型 */
    unsigned char type;
};

#define MY_SWAP(x, y, type) \
        do {    \
            type t;     \
            memcpy ((void*)&t, (void*)x, sizeof (type)); \
            memcpy ((void*)x, (void*)y, sizeof (type)); \
            memcpy ((void*)y, (void*)&t, sizeof (type)); \
        }while(0)


/* 存储目录名的结构 */
struct path_names {

    struct _name *names;
    unsigned int cnt;
    unsigned int size;
};

#endif 
