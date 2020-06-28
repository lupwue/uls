#include "uls.h"

int mx_check_file(t_lit ***args) {
    int sum_file = 0;
    t_lit **arg = *args;

    for (int i = 0; arg[i] != NULL; i++)
        if (!MX_IS_DIR(arg[i]->t_st.st_mode)) {
            arg[i]->what_is_it = 1;
            sum_file++;
        }
    return sum_file;
}

int mx_check_dir(t_lit ***args) {
    int sum_dir = 0;
    t_lit **arg = *args;

    for (int i = 0; arg[i] != NULL; i++)
        if (MX_IS_DIR(arg[i]->t_st.st_mode)) {
            arg[i]->what_is_it = 2;
            sum_dir++;
        }
    return sum_dir;
}

void mx_del(t_lit ***args) {
    t_lit **kill_arr = *args;

    if (kill_arr) {
        for (int i = 0; kill_arr[i] != NULL; i++) {
            mx_strdel(&kill_arr[i]->name);
            mx_strdel(&kill_arr[i]->fullpath);
            if (kill_arr[i]->error)
                mx_strdel(&kill_arr[i]->error);
            free(kill_arr[i]);
            kill_arr[i] = NULL;
        }
        free(*args);
        *args = NULL;
    }
}
