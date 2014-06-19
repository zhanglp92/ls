/*************************************************************************
	> File Name: my_ls.c
	> Author: zhanglp
	> Mail: zhanglp92.gmail.com 
	> Blog: http://blog.csdn.net/zhanglpql 
	> Git: http://github.com/zhanglp92 
	> Created Time: 2014年05月17日 星期六 21时44分24秒
 ************************************************************************/

#include <stdio.h>
#include <my_ls.h>

int main (int argc, const char **argv)
{
    struct path_names pn;

    cmd_analyse (argc, argv, &pn);
    print_ls (&pn);

    destroy_pn (&pn);
    return 0;
}
