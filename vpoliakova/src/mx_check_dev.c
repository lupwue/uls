#include "uls.h"

bool mx_check_dev(t_lit **name, t_sz *size) {
    for (int i = 0; name[i]; i++) {
        if (MX_IS_BLK(name[i]->t_st.st_mode)
            || MX_IS_CHR(name[i]->t_st.st_mode)) {
            return size->is_dev = true;
        }
    }
    return size->is_dev = false;
}
