/*************************************************************************
	> File Name: print_ls.h
	> Author: zhanglp
	> Mail: zhanglp92.gmail.com 
	> Blog: http://blog.csdn.net/zhanglpql 
	> Git: http://github.com/zhanglp92 
	> Created Time: 2014年05月19日 星期一 09时37分25秒
 ************************************************************************/

#ifndef _PRINT_LS_H_
#define _PRINT_LS_H_

#include "my_types.h"
#include <tools.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define COL_INTERVAL    2

struct winsize  ws;


/**
* @brief print_attribute : display attribute of file or other
*
* @param buf : struct stat
* @param path : name 
*/
void print_attribute (struct stat buf, char *path);

/**
* @brief print_l : display attribute carray -l 
*
* @param pn : path names 
*
* @return : size of all file 
*/
unsigned long print_l (const struct path_names *pn);

/**
* @brief display : display don't carray -l 
*
* @param pn : path names
* @param col : cols of a row 
*/
void display (const struct path_names *pn, int col);

/**
* @brief print_ : display don't carray -l 
*
* @param pn : path names 
*/
void print_ (const struct path_names *pn);

/**
* @brief comp_dic : compare function attend to dic 
*
* @param x : 
* @param y : 
*
* @return : 
*/
int comp_dic (const void *x, const void *y);

/**
* @brief comp_atime : compare function attend to atime 
*
* @param x : 
* @param y : 
*
* @return : 
*/
int comp_atime (const void *x, const void *y);

/**
* @brief destroy_pn : destroy path names 
*
* @param pn : path names
*/
void destroy_pn (struct path_names *pn);

/**
* @brief print_ls : display ls 
*
* @param path_names : 
*/
void print_ls (const struct path_names*);

/**
* @brief get_a_dir_content : get content of a diractory 
*
* @param path : name 
* @param pn : path names
*
* @return : 
*/
int get_a_dir_content (const char *path, struct path_names *pn);
void print (const char *path);

#endif
