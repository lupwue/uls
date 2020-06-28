#include "uls.h"

static bool check_aa(char *ds, t_head *head) {
    if (head->flags[mx_get_char_index(MY_FLAGS, 'a')] == 1)
        return true;
     if (head->flags[mx_get_char_index(MY_FLAGS, 'A')] == 1) {
            if (mx_strcmp(ds, ".") == 0 || mx_strcmp(ds, "..") == 0)   
                return false;
            else
                return true;
        }
    if (ds[0] == '.')
        return false;
    return true;
}

static int count_inside_dir(t_lit **new_d, t_head *head) {
    int count = 0;
    t_lit *tmp = *new_d;
    DIR *dtr;
    struct dirent *ds;

    if (tmp && *new_d) {
        (*new_d)->error = NULL;
        lstat(tmp->fullpath, &(tmp->t_st));
        if (MX_IS_DIR(tmp->t_st.st_mode) || MX_IS_LNK(tmp->t_st.st_mode)) {
            if ((dtr = opendir(tmp->fullpath)) != NULL) {
                while ((ds = readdir(dtr)) != NULL)
                    if (check_aa(ds->d_name, head))
                        count++;
                    closedir(dtr);
            }
            else {
                (*new_d)->error = mx_strdup(strerror(errno));
                return -1;
            }
        }
    }
    return count;
}

static t_lit *createnode(char *name, char *path) {
    t_lit *node = (t_lit *)malloc(1 * sizeof(t_lit));

    node->name = mx_strdup(name);
    node->fullpath = mx_strdup(path);
    mx_join(&node->fullpath, "/");
    mx_join(&node->fullpath, name);
    node->error = NULL;
    if (lstat(node->fullpath, &(node->t_st)) == -1)
        node->error = mx_strdup(strerror(errno));
    node->open = NULL;
    return node;
}

static void opendir2(t_lit **new_d, t_head *head) {
   if (*new_d)
        mx_output(new_d, head); 
}

void mx_opendir(t_lit **new_d, t_head *head) {
    DIR *dtr;
    struct dirent *ds;

    for (int i = 0, sum = 0 ; new_d[i] != NULL; i++) {
        if (new_d[i] != 0 && (sum = count_inside_dir(&(new_d[i]), head))) {
            if (sum > 0) {
                new_d[i]->open = malloc((sum + 1) * sizeof(t_lit *));
                if ((dtr = opendir(new_d[i]->fullpath)) != NULL) {
                    for (sum = 0; (ds = readdir(dtr)) != NULL; ) {
                        if (check_aa(ds->d_name, head))
                            new_d[i]->open[sum++]
                            = createnode(ds->d_name, new_d[i]->fullpath);
                        new_d[i]->open[sum] = NULL;
                    }
                closedir(dtr);
                }
            }
        }
    }
    opendir2(new_d, head);
}
