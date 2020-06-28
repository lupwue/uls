#include "uls.h"

t_lit *mx_createnode(char *name) {
    t_lit *node = (t_lit *)malloc(1 * sizeof(t_lit));

    node->name = mx_strdup(name);
    node->fullpath = mx_strdup(name);
    if (lstat(name, &(node->t_st)) == -1)
        node->error = mx_strdup(strerror(errno));
    else
        node->error = NULL;
    node->open = NULL;
    return node;
}

t_lit **mx_createlist(char **name, int count) {
    t_lit **tmp = malloc(count * sizeof(t_lit *));
    int i = 0;

    for (i = 0; name[i]; i++)
        tmp[i] = mx_createnode(name[i]);
    tmp[i] = NULL;
    return tmp;
}

static char **nam(int argc, char **argv, int i, int *count) {
    int j = i;
    char **nam = NULL;

    if (i == argc) {
        *count = 2;
        nam = malloc(2 * sizeof(char *));
        nam[0] = mx_strdup(".");
        nam[1] = NULL;
    }
    else {
        for (; argv[j]; j++) {
        }
        nam = malloc((j - i + 1) * sizeof(char *));
        for (j = 0; argv[i]; i++, j++)
            nam[j] = mx_strdup(argv[i]);
        nam[j] = NULL;
        *count = j + 1;
    }
    return nam;
}

t_lit **mx_getname(int argc, char **argv, int i) {
    int count = 0;
    char **name = nam(argc, argv, i, &count);
    t_lit **args = mx_createlist(name, count);

    mx_del_strarr(&name);
    return args;
}
