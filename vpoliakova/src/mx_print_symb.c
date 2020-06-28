#include "uls.h"

void mx_print_symb(t_lit *name) {
    char *buf = NULL;
    ssize_t nbytes = 0;
    ssize_t buf_size = 0;

    buf_size = name->t_st.st_size == 0 ? 100 : name->t_st.st_size + 1;
    buf = mx_strnew(buf_size);
    nbytes = readlink(name->fullpath, buf, buf_size);
    mx_printstr(" -> ");
    if (nbytes >= 0)
        mx_new_pstr(buf);
    mx_strdel(&buf);
}
