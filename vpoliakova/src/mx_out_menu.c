#include "uls.h"

void mx_out_menu(t_lit **name, t_head *head, int fg) {
    if (*name != NULL) {
        mx_sort(name, head);
        if (head->flags[mx_get_char_index(MY_FLAGS, '1')] == 1)
            mx_one(name);
        if (head->flags[mx_get_char_index(MY_FLAGS, 'm')] == 1)
            mx_out_m(name);
        if (head->flags[mx_get_char_index(MY_FLAGS, 'C')] == 1)
            mx_multi(name);
        if (head->flags[mx_get_char_index(MY_FLAGS, 'l')] == 1)
            mx_long_out(name, head, fg);
    }
}
