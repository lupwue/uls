#include "uls.h"

static void all_output_2(t_lit **new_d, t_head *head) {
    mx_out_menu((*new_d)->open, head, 1);
    if (head->flags[mx_get_char_index(MY_FLAGS, 'R')] == 1) {
        head->output = 1;
        mx_del_fils(&(*new_d)->open, head);
        if ((*new_d)->open) {
            mx_printchar('\n');
            mx_opendir((*new_d)->open, head);
        }
    }
}

static void all_output(t_lit **new_d, t_head *head) {
    if ((*new_d)->open != NULL) {
        all_output_2(new_d, head);
    }
    else if ((*new_d)->error != NULL) {
        char *str = mx_memrchr((*new_d)->name, 
                               '/', mx_strlen((*new_d)->name));

        mx_printerr("uls: ");
        if (!str)
            mx_printerr((*new_d)->name);
        else
            mx_printerr(str + 1);
        mx_printerr(": ");
        mx_printerr((*new_d)->error);
        mx_printerr("\n");
    }
}

static void del_data(t_lit **new_d, t_head *head) {
    for (int i = 0; new_d[i] != NULL; i++) {
        if (head->flags[mx_get_char_index(MY_FLAGS, 'R')] == 0) {
            if (new_d[i]->open) {
                for (int j = 0; new_d[i]->open[j] != NULL; j++) {
                    free(new_d[i]->open[j]->name);
                    free(new_d[i]->open[j]->fullpath);
                    free(new_d[i]->open[j]->error);
                    free(new_d[i]->open[j]);
                }
            }
        }
        free(new_d[i]->name);
        free(new_d[i]->fullpath);
        free(new_d[i]->error);
        free(new_d[i]->open);
        free(new_d[i]);
    }
}

void mx_output(t_lit **new_d, t_head *head) {
    if (new_d) {
        for (int i = 0; new_d[i] != NULL; i++) {
            if (head->output == 1 || head->sum_err > 0) {
                if (new_d[i]->fullpath[0] == '/'
                    && new_d[i]->fullpath[1] == '/')
                    mx_new_pstr(&new_d[i]->fullpath[1]);
                else
                    mx_new_pstr(new_d[i]->fullpath);
                mx_printchar(':');
                mx_printchar('\n');
            }
            all_output(&new_d[i], head);
            if (new_d[i]->error != NULL)
                head->ex = head->ex + 1;
            if (new_d[i + 1])
                mx_printchar('\n');
        }
    }
    if (new_d)
        del_data(new_d, head);
}
