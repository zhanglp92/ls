/*************************************************************************
	> File Name: cmd_analyse.h
	> Author: zhanglp
	> Mail: zhanglp92.gmail.com 
	> Blog: http://blog.csdn.net/zhanglpql 
	> Git: http://github.com/zhanglp92 
	> Created Time: 2014年05月17日 星期六 21时56分41秒
 ************************************************************************/

#ifndef _CMD_ANALYSE_H_
#define _CMD_ANALYSE_H_

#include "my_types.h"
#include <tools.h>

#define E_ARGUMENT  1
#define E_PATH      2

/* 表示文件的最大数目 */
#define FILE_MAX    PATH_BITS

/**
* @brief show_error : display argument of error
*
* @param mode : path error or argument error
* @param str : string 
*/
void show_error (int mode, const char *str);

/**
* @brief arg_analyse : analyse arguments
*
* @param str : string of argument
*
* @return : sucess or fail 
*/
int arg_analyse (const char *str);

/**
* @brief path_analyse : analyse path
*
* @param path : string of path
* @param inode : inode of file 
* @param pn : 
*
* @return : sucess or fail 
*/
int path_analyse (const char *path, unsigned int *inode, struct path_names *pn);

/**
* @brief cmd_analyse : analyse command 
*
* @param int : 
* @param : 
* @param : 
*
* @return 
*/
int cmd_analyse (int, const char **, struct path_names *);

#endif
