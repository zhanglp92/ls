/*************************************************************************
    > File Name: print_ls.c
    > Author: zhanglp
    > Mail: zhanglp92.gmail.com 
    > Blog: http://blog.csdn.net/zhanglpql 
    > Git: http://github.com/zhanglp92 
    > Created Time: 2014年05月19日 星期一 09时37分17秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <print_ls.h>


void print_attribute (struct stat buf, char *path)
{
    /* 打印文件类型 */
    #define DIS_TYPE(type, c) \
        (S_IS ##type (buf.st_mode) ? printf (c) : 0)) ;

    if (DIS_TYPE (LNK, "l")
    else if (DIS_TYPE (REG, "-")
    else if (DIS_TYPE (DIR, "d")
    else if (DIS_TYPE (CHR, "c")
    else if (DIS_TYPE (BLK, "b")
    else if (DIS_TYPE (FIFO, "f")
    else if (DIS_TYPE (SOCK, "s")
    #undef  DIS_TYPE


    #define DIS_CHM(chm, c) \
        (buf.st_mode & S_I ##chm ? printf (c) : printf ("-"))

    DIS_CHM (RUSR, "r");
    DIS_CHM (WUSR, "w");
    buf.st_mode & S_ISUID ? 
        (buf.st_mode & S_IXUSR ? printf ("s") : printf ("S")): 
        DIS_CHM (XUSR, "x");

    DIS_CHM (RGRP, "r");
    DIS_CHM (WGRP, "w");
    buf.st_mode & S_ISGID ? 
        (buf.st_mode & S_IXGRP ? printf ("s") : printf ("S")): 
        DIS_CHM (XGRP, "x");

    DIS_CHM (ROTH, "r");
    DIS_CHM (WOTH, "w");
    buf.st_mode & S_ISVTX ?  
        (buf.st_mode & S_IXOTH ? printf ("t") : printf ("T")): 
        DIS_CHM (XOTH, "x");
    #undef  DIS_CHM 

    printf ("  ");

    struct passwd *psd;
    struct group  *grp;

    /* 打印文件所有者的用户名和组名 */
    psd = getpwuid (buf.st_uid);
    grp = getgrgid (buf.st_gid);

    printf ("%4ld ", buf.st_nlink);
    printf ("%-8s", psd->pw_name);
    printf ("%-8s", grp->gr_name);

    /* 打印文件的大小 */
    printf ("%8ld", buf.st_size);

    char    buf_time[32] = {0}, *tmp;
    if (GET_U_STAT ())  /* 有参数 u 时表示最后一次被访问的时间 */
        tmp = ctime (&buf.st_atime);
    else                /* 没有参数 u 时表示最后u一次修改的时间 */
        tmp = ctime (&buf.st_mtime);
        
    strncpy (buf_time, tmp, strlen (tmp)-1);
    printf ("  %-20s ", buf_time); 
    printf ("%s\n", path);
}

unsigned long print_l (const struct path_names *pn)
{
    int             i;
    struct stat     buf;
    unsigned long   size = 0;
    char            path[PATH_LEN] = {0};

    int     len = strlen (pn->names[0].val);
    for (i = 1; i < pn->cnt; i++) {

        /* 组合文件名 */
        memset (path, 0, sizeof (path));
        strncpy (path, pn->names[0].val, len); 
        strncat (path, pn->names[i].val, strlen (pn->names[i].val)); 
        if (0 > lstat (path, &buf)) {
            
            perror ("stat");
            continue;
        }
        print_attribute (buf, pn->names[i].val);

    //    size += buf.st_size;
        if (strncmp (".", pn->names[i].val, 2) && strncmp ("..", pn->names[i].val, 3)) 
            size += (buf.st_blocks);
    }

    return size;
}


void display (const struct path_names *pn, int col) 
{
    if (0 == col)  return ;
    int     i, j, k, t;
    /* 得到有多少行, pn->cnt-1 是因为第一项是本目录的路径, 不是目录的内容 */
    int     row = (pn->cnt-1) / col + ((pn->cnt-1) % col ? 1 : 0);
    int     lens[col];  /* 记录每列中最长的串下标 */ 

//    printf ("r %d, c %d, cnt %d \n", row, col, pn->cnt-1);

    /* 求得每列中的最长字符串的长度 */
    memset (lens, 0, sizeof (int) * col);
    for (k = 1, j = 0; j < col; j++) {

        for (i = 0; i < row; i++, k++) {

            if (k >= pn->cnt) {
                break ;
            /* 这里给最大长度加 COL_INTERVAL 表示每两列之间隔开的距离 */
            } else if (lens[j] < (t = strlen (pn->names[k].val)+COL_INTERVAL)) 
                lens[j] = t; 
        }
    }
    /* 最后一列不用加间距 */
    lens[col-1] -= COL_INTERVAL;

    for (i = 0; i < row; i++) {

        for (j = 0; j < col; j++) {
            /* 计算 (i,j) 位置要打印的文件*/
            k = i + row * j + 1; 
            if (k >= pn->cnt) {
                break;

            } else { 

                printf ("%s", pn->names[k].val);
                /* 用空格补齐剩余的位置, 最后一列不用补齐(不用实现) */
                for (t = lens[j] - strlen (pn->names[k].val); t; t--) 
                    printf (" ");
            }
        }
        printf ("\n");
    }
}

unsigned get_row_len (const struct path_names *pn, const unsigned *lens, unsigned col) 
{
    if (0 == col) return 0;
    unsigned     k, i, j, sum, t, len;
    unsigned     row = (pn->cnt-1) / col + ((pn->cnt-1) % col ? 1 : 0);

    for (k = 1, sum = j = 0; j < col; j++) {

        for (len = i = 0; i < row; i++, k++) {

            if (k >= pn->cnt) {
                break ;
            /* 这里给最大长度加 COL_INTERVAL 表示每两列之间隔开的距离 */
            } else if (len < (t = lens[k]+COL_INTERVAL)) 
                len = t; 
        }
        sum += len;
    }
    /* 最后一列不用加间距 */
    sum -= COL_INTERVAL;
    return sum;
}

void print_ (const struct path_names *pn)
{
    int     i;
    unsigned lens[pn->cnt];
    memset (lens, 0, sizeof (unsigned) * pn->cnt);
    lens[0] = PATH_LEN+1;

    /* 求得所有串的长度,将最长串的长度放在第0个位置 */ 
    for (i = 1; i < pn->cnt; i++) {

        lens[i] = strlen (pn->names[i].val);
        if (lens[0] > lens[i]) 
            lens[0] = lens[i]; 
    }

    if (0 == lens[0]) return ;
    /* 首先粗略的估算一行可以排列多少个(最多), 然后在给减1 进行尝试 */
    /* 终端宽度除最小串的长度加间距 */
    unsigned col = ws.ws_col / lens[0]; 
    
    /* 得到合适的 col 值（有多少列） */
    while (get_row_len (pn, lens, col) > ws.ws_col) 
        col--;
    /* 竖着排序打印 */
    display (pn, col);
}

/* 比较函数, 按照字典顺序 */
int comp_dic (const void *x, const void *y)
{
    char *p = ((struct _name*)x)->val;
    char *q = ((struct _name*)y)->val;
    int     i;

    for (i = 0; '.' == p[i]; i++) ;
    p += i;

    for (i = 0; '.' == q[i]; i++) ;
    q += i;

    int lenx = strlen (p); 
    int leny = strlen (q); 
    int len = lenx > leny ? lenx+1 : leny+1; 
    return strncasecmp (p, q, len); 
} 

/* 比较最后一次访问的时间 */
int comp_atime (const void *x, const void *y) 
{
    struct stat bufx, bufy;


    if (0 > lstat ((char*)x, &bufx) || 
        0 > lstat ((char*)y, &bufy)) {
            perror ("lstat");
        }

    return bufy.st_atime - bufx.st_atime;
}

/* 得到一个目录中的内容，存储在 path_names 结构中 */
int get_a_dir_content (const char *path, struct path_names *pn) 
{
    DIR             *dir_ptr;
    struct dirent   *direntp;

    if (NULL == (dir_ptr = opendir (path))) { 

        fprintf (stderr, "ls: cannot open %s \n", path); 
        return FAIL;
    }else {
        
        /* 首先添加本目录的名字 */
        add_path_to_path_names (pn, path, DT_DIR); 
        while (NULL != (direntp = readdir (dir_ptr))) {
 
            /* 如果没有参数 -a 则不显示隐藏文件 */
            if (0 == GET_A_STAT () && '.' == direntp->d_name[0]) 
                continue;

            add_path_to_path_names (pn, direntp->d_name, direntp->d_type); 
        }

        closedir (dir_ptr);
    }

    /* 如果没有读到内容则，直接退出 */
    if (1 >= pn->cnt) return SUCESS;

    /* 有u 没有 l时，按照最后一次被访问的时间排序 */
    if (GET_U_STAT () && 0 == GET_L_STAT ()) { 

        qsort (pn->names+1, pn->cnt-1, sizeof (struct _name), comp_atime);
    }else {

        qsort (pn->names+1, pn->cnt-1, sizeof (struct _name), comp_dic);
    } 

    if ( GET_A_STAT () ) {
    
        int             i, f = 0;
        /* 将 ./ 和 ../ 放在第1,2个位置 */
        for (i = 1; i < pn->cnt && f < 2; i++) {
            
            if (0 == strncmp ("./\0", pn->names[i].val, 3)) {

                MY_SWAP (&pn->names[1], &pn->names[i], struct _name);
                f++;
            }else if (0 == strncmp ("../\0", pn->names[i].val, 4)) {
                
                MY_SWAP (&pn->names[2], &pn->names[i], struct _name);
                f++;
            }
        }
    }

    return SUCESS;
}

/* 记录总的项目数,总的大小 */
unsigned long long    _my_cnt;
unsigned long long    _my_size; 
void print (const char *path) 
{
    struct path_names   pn = {0}; 

    /* 得到指定路径的内容, 存储在 path_names 数组中 */ 
    if (FAIL == get_a_dir_content (path, &pn)) 
        return ;

    printf ("\n%s (数目：%d):\n", path, pn.cnt-1); 
    /* 如果此目录为空时，则退出 */
    if (1 == pn.cnt) 
        return ;

    /* 按照某种方式显示 */
    if (0 == GET_L_STAT ()) { 

        print_ (&pn); 
    }else { 

        _my_size += print_l (&pn); 
    }
    _my_cnt += pn.cnt-1;

    /* 递归 */
    if ( GET_R_STAT () ) {
        
        char    buf[PATH_LEN] = {0};
        int     len = strlen (pn.names[0].val);
        strncpy (buf, pn.names[0].val, len);

        /* 递归时跳过 . 和 .. 目录 */
        int     i = GET_A_STAT () ? 3 : 1; 
        for (i; i < pn.cnt; i++) {
            
            if (DT_DIR & pn.names[i].type) {

                strncpy (buf+len, pn.names[i].val, strlen (pn.names[i].val)+1);
        //        getchar ();
                print (buf);
            }
        }

    }
    destroy_pn (&pn); 
}

void print_ls (const struct path_names *pn)
{
    if ( isatty (STDOUT_FILENO) == 0) 

        exit(1); 
        
    if( ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws) < 0) {

        perror("ioctl TIOCGWINSZ error");
        exit(1);
    } 
//    printf("%d rows, %d columns\n", ws.ws_row, ws.ws_col); 

    int     i; 
    /* 将指定的文件首先列出来 */
    struct path_names   file = {0};
    add_path_to_path_names (&file, "", 0); 
    for (i = 1; i < pn->cnt; i++) {

        if (!(DT_DIR & pn->names[i].type)) {
            
            add_path_to_path_names (&file, pn->names[i].val, pn->names[i].type);
        }
    }
    if (1 < file.cnt) {
        
        GET_L_STAT () ? print_l (&file) : print_ (&file); 
    }

    /* 是否有指定路径 */ 
    i = 1 == pn->cnt ? 0 : 1;
    for (i; i < pn->cnt; i++) { 
        /* 非目录的文件已经在上边处理过了 */
        if (DT_DIR & pn->names[i].type)
            print (pn->names[i].val); 
    }

    if (GET_L_STAT ())

        printf ("总数：%llu , 总用量：%llu \n", _my_cnt, _my_size*512/1024);
    else 

        printf ("总数：%llu \n", _my_cnt);
}

void destroy_pn (struct path_names *pn)
{
    free (pn->names);
}
