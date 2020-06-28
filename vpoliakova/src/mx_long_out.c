#include "uls.h"

static char *check_pw(t_lit *total) {
    struct passwd *pw = NULL;
    char *name = NULL;

    pw = getpwuid(total->t_st.st_uid);
    if (pw) {
        name = mx_strdup(pw->pw_name);
        return name;
    }
    else {
        name = mx_itoa(total->t_st.st_uid);
        return name;
    }
}

static char *check_grp(t_lit *total) {
    struct group *grp = NULL;
    char *name = NULL;

    grp = getgrgid(total->t_st.st_gid);
    if (grp) {
        name = mx_strdup(grp->gr_name);
        return name;
    }
    else {
        name = mx_itoa(total->t_st.st_gid);
        return name;
    }
}

static void count_size(t_sz *size, t_lit *total) {
    char *name_grp = check_grp(total);
    char *name_pw = check_pw(total);

    if (size->lnk < total->t_st.st_nlink)
        size->lnk = total->t_st.st_nlink;
    if (size->sz < total->t_st.st_size)
        size->sz = total->t_st.st_size;
    if (size->group < mx_strlen(name_grp))
        size->group = mx_strlen(name_grp);
    if (size->usr < mx_strlen(name_pw))
        size->usr = mx_strlen(name_pw);
    free(name_grp);
    free(name_pw);
}

void mx_long_out(t_lit **name, t_head *head, int fg) {
    t_sz *size = malloc(sizeof(t_sz));
    int blk_size = 0;
    int i = 0;

    mx_memset(size, 0, sizeof(t_sz));
    for (int i = 0; name[i]; i++) {
        blk_size += name[i]->t_st.st_blocks;
        count_size(size, name[i]);
    }
    if (fg == 1) {
        mx_printstr("total ");
        mx_printint(blk_size);
        mx_printchar('\n');
    }
    mx_check_dev(name, size);
    for (i = 0; name[i]; i++)
        mx_print(name[i], size, head);
    free(size);
}
