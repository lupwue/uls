#include "uls.h"
void mx_add_new_dir_array(t_lit **args, t_lit **new_d) {
    int count_new_arg = 0;

    new_d[count_new_arg] = NULL;
    for (int i = 0; args[i] != NULL; i++) {
        if (args[i]->what_is_it == 2) {
            new_d[count_new_arg] = (t_lit *)malloc(sizeof(t_lit));
            new_d[count_new_arg]->name = mx_strdup(args[i]->name);
            new_d[count_new_arg]->fullpath = mx_strdup(args[i]->fullpath);
            new_d[count_new_arg]->t_st = args[i]->t_st;
            new_d[count_new_arg]->open = NULL;
            new_d[count_new_arg]->error = NULL;
            count_new_arg++;
        }
    }
    new_d[count_new_arg] = NULL;
}

void mx_add_new_file_array(t_lit **args, t_lit **new_f) {
    int count_new_arg = 0;

    new_f[count_new_arg] = NULL;
    for (int i = 0; args[i] != NULL; i++) {
        if (args[i]->what_is_it == 1) {
            new_f[count_new_arg] = (t_lit *)malloc(sizeof(t_lit));
            new_f[count_new_arg]->name = mx_strdup(args[i]->name);
            new_f[count_new_arg]->fullpath = mx_strdup(args[i]->fullpath);
            new_f[count_new_arg]->t_st = args[i]->t_st;
            new_f[count_new_arg]->open = NULL;
            new_f[count_new_arg]->error = NULL;
            count_new_arg++;
        }
    }
    new_f[count_new_arg] = NULL;
}

static void ind_args2(t_lit **args, t_head *head, 
                      t_lit **new_f, t_lit **new_d) {
    if ((head->sum_dir > 0 && head->sum_file > 0)  || head->sum_dir > 1)
        head->output = 1;
    if (head->sum_file) {
        new_f = (t_lit **)malloc((head->sum_file + 1) * sizeof(t_lit *));
        mx_add_new_file_array(args, new_f);
    }
    if (head->sum_dir) {
        new_d = (t_lit **)malloc((head->sum_dir + 1) * sizeof(t_lit *));
        mx_add_new_dir_array(args, new_d);
    }
    if (new_f) {
        mx_out_menu(new_f, head, 0);
        mx_del(&new_f);
        if (head->sum_dir)
            mx_printchar('\n');
    }
    if (new_d != NULL) {
        mx_opendir(new_d, head);
        free(new_d);
    }
}

void mx_indification_args(t_lit **args, t_head *head) {
    t_lit **new_f = NULL;
    t_lit **new_d = NULL;

    head->sum_dir = mx_check_dir(&args);
    head->sum_file = mx_check_file(&args);
    ind_args2(args, head, new_f, new_d);
}
