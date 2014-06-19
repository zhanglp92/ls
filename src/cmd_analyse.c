/*************************************************************************
	> File Name: cmd_analyse.c
	> Author: zhanglp
	> Mail: zhanglp92.gmail.com 
	> Blog: http://blog.csdn.net/zhanglpql 
	> Git: http://github.com/zhanglp92 
	> Created Time: 2014年05月17日 星期六 21时55分19秒
 ************************************************************************/

#include <stdio.h>
#include <cmd_analyse.h>
#include <sys/stat.h>
#include <string.h>

void show_error (int mode, const char *str)
{
    if (E_ARGUMENT == mode)

        printf ("ls：无效选项 -- %c \n", str[0]);

    else if (E_PATH == mode) 

        printf ("ls: 无法访问%s: 没有那个文件或目录 \n", str);
}

int arg_analyse (const char *str) 
{
    char    *args = ARGS;
    int     pos, k;

    for (pos = 0; str[pos]; pos++) {
        
        for (k = 0; args[k]; k++) {

            if (str[pos] == args[k]) {

                _argc |= 1 << k;
                break;
            }
        }

        if (0 == args[k]) {
            
            show_error (E_ARGUMENT, str+pos);
            return FAIL;
        }
    }

    return SUCESS;
}

int path_analyse (const char *path, unsigned int *inode, struct path_names *pn) 
{
    struct stat buf; 

    if (-1 == stat (path, &buf)) {

        show_error (E_PATH, path);
        return FAIL;
    }

    int     i;

    /* 去除重复的路径 */
    for (i = 0; i < pn->cnt; i++) { 

        if (inode[i] == buf.st_ino) 

            return SUCESS; 
    }
    /* 加入inode 到数组中 */
    inode[i] = buf.st_ino;
    /* 将新的路径加入, 类型右移 12 位为了和 readdir 得到的类型匹配 */
    add_path_to_path_names (pn, path, buf.st_mode >> 12);

    return SUCESS;
}

int cmd_analyse (int argc, const char **argv, struct path_names *pn) 
{
    memset (pn, 0, sizeof (struct path_names));
    /* 记录文件的 inode 避免后边打印重复的文件 */
    unsigned int    inode[FILE_MAX] = {0}; 

    /* 将当前目录添加到 pn 的第一项中 */
    add_path_to_path_names (pn, ".", DT_DIR);
    int     i;
    for (i = 1; i < argc; i++) {

        if ('-' == argv[i][0]) {

            if (FAIL == arg_analyse (argv[i]+1))
                return FAIL;
        }else {
            
            if (FAIL == path_analyse (argv[i], inode, pn)) 
                return FAIL; 
        }
    }

    return SUCESS;
}
