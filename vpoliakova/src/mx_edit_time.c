#include "uls.h"

void mx_edit_time(t_lit *name, char *t, t_head *head) {
    int i = 0;

    if (head->flags[mx_get_char_index(MY_FLAGS, 'T')] == 1) {
        for (i = 4; i < t[i]; i++)
            mx_printchar(t[i]);
    }
    else {
        if (1565913600 >= name->t_st.st_mtime) {
            for (i = 4; i < 10; i++)
                mx_printchar(t[i]);
            mx_printstr("  ");
            for (i = 20; i < 24; i++)
                mx_printchar(t[i]);
        }
        else 
            for (i = 4; i < 16; i++)
                mx_printchar(t[i]);
    }
    mx_printstr(" ");
}
