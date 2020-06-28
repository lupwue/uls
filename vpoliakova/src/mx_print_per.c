#include "uls.h" 

char mx_get_file_acl(t_lit *name) {
    acl_t tmp;

    if (listxattr(name->fullpath, NULL, 0, XATTR_NOFOLLOW) > 0)
        return ('@');
    if ((tmp = acl_get_file(name->fullpath, ACL_TYPE_EXTENDED))) {
        acl_free(tmp);
        return ('+');
    }
    return (' ');
}

char mx_check_perm(t_lit *name) {
    if (MX_IS_DIR(name->t_st.st_mode))
        return 'd';
    if (MX_IS_LNK(name->t_st.st_mode))
        return 'l';
    if (MX_IS_BLK(name->t_st.st_mode))
        return 'b';
    if (MX_IS_CHR(name->t_st.st_mode))
        return 'c';
    if (MX_IS_FIFO(name->t_st.st_mode))
        return 'p';
    if (MX_IS_SOCK(name->t_st.st_mode))
        return 's';
    if (MX_IS_WHT(name->t_st.st_mode))
        return 'w';
    return '-';
}

static char check_chmode2(char *chmod) {
    if (chmod[9] == '-')
        return chmod[9] = 'T';
    else 
        return chmod[9] = 't';
}

static char check_chmode1(char chmod) {
    if (chmod == '-')
        return chmod = 'S';
    else
        return chmod = 's';
}

void mx_print_per(t_lit *name) {
    char chmod[12];

    chmod[0] = mx_check_perm(name);
    chmod[1] = (S_IRUSR & name->t_st.st_mode) ? 'r' : '-';
    chmod[2] = (S_IWUSR & name->t_st.st_mode) ? 'w' : '-';
    chmod[3] = (S_IXUSR & name->t_st.st_mode) ? 'x' : '-';
    chmod[4] = (S_IRGRP & name->t_st.st_mode) ? 'r' : '-';
    chmod[5] = (S_IWGRP & name->t_st.st_mode) ? 'w' : '-';
    chmod[6] = (S_IXGRP & name->t_st.st_mode) ? 'x' : '-';
    chmod[7] = (S_IROTH & name->t_st.st_mode) ? 'r' : '-';
    chmod[8] = (S_IWOTH & name->t_st.st_mode) ? 'w' : '-';
    chmod[9] = (S_IXOTH & name->t_st.st_mode) ? 'x' : '-';
    chmod[10] = mx_get_file_acl(name);
    chmod[11] = '\0';
    S_ISUID & name->t_st.st_mode ? chmod [3] = check_chmode1(chmod[3]) : 0;
    S_ISGID & name->t_st.st_mode ? chmod [6] = check_chmode1(chmod[6]) : 0;
    S_ISVTX & name->t_st.st_mode ? chmod [9] = check_chmode2(chmod) : 0;
    for (int i = 0; chmod[i]; i++) 
        mx_printchar(chmod[i]);
    mx_printchar(' ');
}
