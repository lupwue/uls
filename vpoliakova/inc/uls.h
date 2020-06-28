#ifndef PATH_H
#define PATH_H

#include <string.h>
#include <errno.h>
#include "libmx.h"
#include "sys/stat.h"
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/ioccom.h>
#include <pwd.h>

#define MX_IS_BLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define MX_IS_CHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define MX_IS_DIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#define MX_IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define MX_IS_SOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#define MX_IS_FIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define MX_IS_WHT(mode) (((mode) & S_IFMT) == S_IFWHT)
#define MX_IS_REG(mode) (((mode) & S_IFMT) == S_IFREG)
#define MX_IS_EXEC(mode) ((mode) & S_IXUSR)

#define MY_FLAGS "ACLRSTalmrt1"
#define LS_COLOR_RED        "\x1b[31m"
#define LS_COLOR_RESET      "\x1b[0m"

struct stat *buf;

typedef struct s_lit {
    char *name;
    char *fullpath;
    char *error;
    int what_is_it;
    struct stat t_st;
    struct s_lit **open;
}              t_lit;

typedef struct s_head {
    int *flags;
    int count_flags;
    int sum_dir;
    int sum_file;
    int sum_err;
    int output;
    int ex;
}              t_head;

typedef struct s_sz {
    int lnk;
    int sz;
    int group;
    int usr;
    bool is_dev;
}              t_sz;

int mx_check_flags(int argc, char *argv[], t_head *head);
t_lit **mx_getname(int argc, char **argv, int i);
void mx_parse(int argc, char **argv, t_head *head);
void mx_sort_asci(t_lit ***arg);
t_lit **mx_make_new_list(t_lit **args, int valid_node);
void mx_del_list(t_lit ***args);
void mx_indification_args(t_lit **args, t_head *head);
int mx_check_dir(t_lit ***args);
int mx_check_file(t_lit ***args);
t_lit **mx_createlist(char **name, int count);
void mx_opendir(t_lit **new_d, t_head * head);
void mx_join(char **res, char *s2);
void mx_add_new_dir_array(t_lit **args, t_lit **new_d);
void mx_add_new_file_array(t_lit **args, t_lit **new_f);
t_lit** mx_arg(t_lit **args);
void mx_del_fils(t_lit ***args, t_head *head);
void mx_del_litarr(t_lit ***args, t_lit **dir);
int mx_check_file(t_lit ***args);

void mx_output(t_lit **new_d, t_head *head);
void mx_del(t_lit ***args);
void mx_out_menu(t_lit **name, t_head *head, int i);
void mx_long_out(t_lit **name, t_head *head, int fg);
bool mx_check_dev(t_lit **name, t_sz *size);
void mx_print(t_lit *name, t_sz *size, t_head *head);
void mx_print_lnk(t_lit *name, t_sz *size);
void mx_print_per(t_lit *name);
void mx_get_user_name(t_lit *name, int usr);
char mx_check_perm(t_lit *name);
void mx_get_group_name(t_lit *name, int group);
char *mx_get_minor(t_lit *name);
char *mx_get_major(t_lit *name);
void mx_print_sz(t_lit *name, t_sz *size);
void mx_edit_time(t_lit *name, char *t, t_head *head);
void mx_print_symb(t_lit *name);
void mx_sort(t_lit **new_d, t_head *head);
void mx_one(t_lit **new_d);
void mx_multi(t_lit **new_d);
void mx_out_m(t_lit **new_d);

#endif


