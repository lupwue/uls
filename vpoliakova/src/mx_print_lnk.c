#include "uls.h"

void mx_print_lnk(t_lit *name, t_sz *size) {
    int counter = 0;
    char *res_now = mx_itoa(name->t_st.st_nlink);
    char *res_lnk = mx_itoa(size->lnk);

    if (mx_strlen(res_now) == mx_strlen(res_lnk)) {
        mx_printint(name->t_st.st_nlink);
    }
    else if (mx_strlen(res_now) < mx_strlen(res_lnk)) {
        counter = mx_strlen(res_now);
        while (counter != mx_strlen(res_lnk)) {
            mx_printchar(' ');
            counter++;
        }
        mx_printint(name->t_st.st_nlink);
    }
    mx_printchar(' ');
    free(res_now);
    free(res_lnk);
}
