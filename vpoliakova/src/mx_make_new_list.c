#include "uls.h"

void mx_del_list(t_lit ***args) {
    for (int i = 0; (*args)[i] != NULL; i++) {
        free((*args)[i]->name);
        free((*args)[i]->fullpath);
        if ((*args)[i]->error)
            free((*args)[i]->error);
        (*args)[i]->name = NULL;
        (*args)[i]->fullpath = NULL;
        (*args)[i]->error = NULL;
        free((*args)[i]);
        (*args)[i] = NULL;
    }
    free(*args);
    *args = NULL;
}

t_lit **mx_make_new_list(t_lit **args, int valid_node) {
    t_lit **newstruct = (t_lit **)malloc((valid_node + 1) * sizeof(t_lit *));
    int count_new_lst = 0;

    for (int i = 0; args[i] != NULL; i++) {
        if (!args[i]->error) {
            newstruct[count_new_lst] = (t_lit *)malloc(sizeof(t_lit));
            newstruct[count_new_lst]->name = mx_strdup(args[i]->name);
            newstruct[count_new_lst]->fullpath = mx_strdup(args[i]->fullpath);
            newstruct[count_new_lst]->t_st = args[i]->t_st;
            count_new_lst++;
        }
    }
    newstruct[count_new_lst] = NULL;
    mx_del_list(&args);
    return newstruct;
}
