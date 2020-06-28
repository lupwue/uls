#include "uls.h"

void mx_del_litarr(t_lit ***args, t_lit **dir) {
    t_lit **kill_arr = *args;

    for (int i = 0; kill_arr[i] != NULL; i++) {
        mx_strdel(&kill_arr[i]->name);
        mx_strdel(&kill_arr[i]->fullpath);
        if (kill_arr[i]->error != NULL)
            mx_strdel(&kill_arr[i]->error);
        free(kill_arr[i]);
        kill_arr[i] = NULL;
        }
        free(*args);
        *args = dir;
}
