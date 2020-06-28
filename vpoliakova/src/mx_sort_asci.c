#include "uls.h"

static void swapnode(t_lit **st1, t_lit **st2) {
    t_lit *tmp = *st1;

    *st1 = *st2;
    *st2 = tmp;
}

static int sizearr(t_lit **arg) {
    int i = 0;

    while (arg[i])
        i++;
    return i;
}

void mx_sort_asci(t_lit ***arg) {
    t_lit **args = *arg;
    int size = sizearr(args);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (mx_strcmp(args[i]->name, args[j]->name) > 0)
                swapnode(&(args[i]), &(args[j]));
        }
    }
    **arg = *args;
}
