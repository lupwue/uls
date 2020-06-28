#include "uls.h"

static void printn(int *len) {
    (*len) = 0;
    mx_printchar('\n');
}

static void print_names(t_lit **new_d, int wincol) {
    int len = 0;
    int nextlen = 0;

    for (int i = 0; new_d[i] != NULL; i++) {
            mx_new_pstr(new_d[i]->name);
        len += mx_strlen(new_d[i]->name) + 2;
        if (new_d[i + 1]) {
            mx_new_pstr(", ");
            if (new_d[i + 2])
                nextlen = 3;
            else
                nextlen = 1;
            if (len + nextlen + mx_strlen(new_d[i + 1]->name)
                > wincol)
                printn(&len);
        }
    }
    mx_printchar('\n');
}

void mx_out_m(t_lit **new_d) {
    struct winsize win;

    if (!new_d)
        return;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (isatty(1))
        print_names(new_d, win.ws_col);
    else
        print_names(new_d, 80);
}
