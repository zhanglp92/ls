/*************************************************************************
	> File Name: my_types.c
	> Author: zhanglp
	> Mail: zhanglp92.gmail.com 
	> Blog: http://blog.csdn.net/zhanglpql 
	> Git: http://github.com/zhanglp92 
	> Created Time: 2014年05月19日 星期一 11时26分41秒
 ************************************************************************/

#include<stdio.h>
#include <my_types.h>
#include <stdlib.h>
#include <string.h>

int add_path_to_path_names (struct path_names *pn, const char *path, unsigned char type)
{
    /* 扩展存储路径名的数组 */
    if (pn->cnt >= pn->size) {
        
        pn->size = 2 * pn->size + 1;
        if (NULL == (pn->names = realloc (pn->names, sizeof (struct _name) * pn->size))) {

            exit (1);
        //    return FAIL;
        }
    }

    pn->names[pn->cnt].type = type;
    /* 存储一个路径名 */


    int     len = strlen (path);
    strncpy (pn->names[pn->cnt].val, path, len); 
    if (DT_DIR == type) {
        
        /* 使路径后边带上‘/’ */
        if ('/' != path[len-1]) 

            pn->names[pn->cnt].val[len++] = '/';

    }
    pn->names[pn->cnt++].val[len] = 0;

    return SUCESS;
}
