#include "uls.h"

void mx_get_user_name(t_lit *name, int usr) {
    struct passwd *pw = getpwuid(name->t_st.st_uid);
    int counter = 0;
    char *print = NULL;

    if (pw)
        print = mx_strdup(pw->pw_name);
    else
        print = mx_itoa(name->t_st.st_uid);
    if (mx_strlen(print) == usr)
        mx_printstr(print);
    else if (mx_strlen(print) < usr) {
        counter = mx_strlen(print);
        mx_printstr(print);
        while (counter != usr) {
            mx_printchar(' ');
            counter++;
        }
    }
    mx_printstr("  ");
    free(print);
}

void mx_get_group_name(t_lit *name, int group) {
    struct group *grp = getgrgid(name->t_st.st_gid);
    int counter = 0;
    char *print = NULL;

    if (grp) 
        print = mx_strdup(grp->gr_name);
    else
        print = mx_itoa(name->t_st.st_gid);
    if (mx_strlen(print) == group)
        mx_printstr(print);
    else if (mx_strlen(print) < group) {
        counter = mx_strlen(print);
        mx_printstr(print);
        while (counter != group) {
            mx_printchar(' ');
            counter++;
        }
    }
    mx_printstr("  ");
    free(print);
}
