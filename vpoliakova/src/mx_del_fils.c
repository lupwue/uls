#include "uls.h"

static t_lit *create_file_node(t_lit *arg) {
    t_lit *node = (t_lit *)malloc(1 * sizeof(t_lit));

    node->name = mx_strdup(arg->name);
    node->fullpath = mx_strdup(arg->fullpath);
    node->error = NULL;
    if (arg->error != NULL)
        node->error = mx_strdup(arg->error);
    lstat(node->fullpath, &(node->t_st));
    if (arg->open != NULL)
        node->open = arg->open;
    else
        node->open = NULL;
    return node;

}

static void create_fd(t_lit ***dirs, t_lit ***args) {
    int sum_dir = 0;

    for (int i = 0; (*args)[i] != NULL; i++)
        if ((*args)[i]->error == NULL)
            if (MX_IS_DIR((*args)[i]->t_st.st_mode) &&
                mx_strcmp((*args)[i]->name, ".") != 0 &&
                mx_strcmp((*args)[i]->name, "..") != 0)
                sum_dir++;
        if (sum_dir > 0)
            *dirs = malloc((sum_dir + 1) * sizeof(t_lit *));
}

void mx_del_fils(t_lit ***args, t_head *head) {
    t_lit **dirs = NULL;
    int sum_dir = 0;

    create_fd(&dirs, args);
    for (int i = 0; (*args)[i] != NULL; i++) {
        if ((*args)[i]->error == NULL) {
            if (MX_IS_DIR((*args)[i]->t_st.st_mode) &&
                mx_strcmp((*args)[i]->name, ".") != 0 &&
                mx_strcmp((*args)[i]->name, "..") != 0) {
                dirs[sum_dir++] = create_file_node((*args)[i]);
                dirs[sum_dir] = NULL;
            }
        }
    }
    head->sum_file = 1;
    mx_del_litarr(args, dirs);
}
