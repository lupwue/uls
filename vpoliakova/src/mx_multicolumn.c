#include "uls.h"

int max_len_new_d(t_lit **new_d) {
    int max = 0;
    int temp = 0;

    for (int i = 0; new_d[i]; i++) {
        temp = mx_strlen(new_d[i]->name);
        if (temp > max)
            max = temp;
    }
    if (max % 8 == 0)
        max += 8;
    else
        max = 8 - (max % 8) + max;
    return max;
}

void mx_print_tab(int len, int maxlen) {
    int count = 0;
    int p;

    p = maxlen - len;
    if (p % 8 != 0)
        count = (p / 8) + 1;
    else
        count = p / 8;
    for (int i = 0; i < count; i++)
        mx_printchar('\t');
}

static void printcols(t_lit **new_d, int rows, int num, int maxlen) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; i + j < num; j += rows) {
            mx_new_pstr(new_d[i + j]->name);
            if (new_d[i + j + 1] && (i + j + rows < num))
                mx_print_tab(mx_strlen(new_d[i + j]->name), maxlen);
        }
        if (i != rows - 1)
            mx_printchar('\n');
    }
}

static void print_new_d(t_lit **new_d, int maxlen, int wincol) {
    int rows;
    int cols = (wincol / maxlen) != 0 ? wincol / maxlen : 1;
    int num = 0;

    for (;new_d[num]; num++) {
    }
    if (maxlen * cols > wincol && cols != 1)
        cols--;
    if (num * maxlen > wincol) {
        rows = num / cols;
        if (rows == 0 || num % cols != 0)
            rows += 1;
        printcols(new_d, rows, num, maxlen);
    }
    else
        for (int i = 0; new_d[i]; i++) {
            mx_new_pstr(new_d[i]->name);
            if (new_d[i + 1]) 
                mx_print_tab(mx_strlen(new_d[i]->name), maxlen);
        }
        mx_printchar('\n');
}

void mx_multi(t_lit **new_d) {
    int maxlen;
    struct winsize win;

    if (!new_d)
        return;
    maxlen = max_len_new_d(new_d);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    if (isatty(1))
        print_new_d(new_d, maxlen, win.ws_col);
    else
        print_new_d(new_d, maxlen, 80);
}

