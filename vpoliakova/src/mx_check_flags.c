#include "uls.h"

static void illegal_option(char c) {
    mx_printerr("uls: illegal option -- ");
    write(2, &c, 1);
    mx_printerr("\nusage: uls [-");
    mx_printerr(MY_FLAGS);
    mx_printerr("] [file ...]\n");
    exit(1);
}

static void parse_sorts(char c, t_head *head) {
    char *sorts = "rtucS";

    if (mx_get_char_index(sorts, c) != -1 
        && head->flags[mx_get_char_index(MY_FLAGS, 'S')] != 1)
    head->flags[mx_get_char_index(MY_FLAGS, c)] = 1;
}

static void parse_type_output(char c, t_head *head) {
    char *out = "l1mC";

    if (mx_get_char_index(out, c) != -1) {
        if (c == 'C' && head->flags[mx_get_char_index(MY_FLAGS, 'm')] == 1) {
            
        }
        else {
            head->flags[mx_get_char_index(MY_FLAGS, 'l')] = 0;
            head->flags[mx_get_char_index(MY_FLAGS, 'm')] = 0;
            head->flags[mx_get_char_index(MY_FLAGS, 'C')] = 0;
            head->flags[mx_get_char_index(MY_FLAGS, '1')] = 0;
            head->flags[mx_get_char_index(MY_FLAGS, c)] = 1;
        }
    }
    if (c == 'T')
        head->flags[mx_get_char_index(MY_FLAGS, 'T')] = 1;
    if (c == 'R' || c == 'a' || c == 'A')
        head->flags[mx_get_char_index(MY_FLAGS, c)] = 1;
    parse_sorts(c, head);
}

static void if_isatty(t_head *head) {
    if (isatty(1))
        head->flags[mx_get_char_index(MY_FLAGS, 'C')] = 1;
    else 
        head->flags[mx_get_char_index(MY_FLAGS, '1')] = 1;
}

int mx_check_flags(int argc, char *argv[], t_head *head) {
    int res = 1;

    if_isatty(head);
    for (int i = 1; i < argc && argv[i][0] == '-'; i++) {
        if (argv[i][0] == '-' && !argv[i][1])
            return res;
        if (mx_strcmp(argv[i], "--") == 0)
            return res + 1;
        if (argv[i][0] == '-') {
            res ++;
            for (int j = 1; argv[i][j]; j++) {
                parse_type_output(argv[i][j], head);
                if (mx_get_char_index(MY_FLAGS, (argv[i][j])) == -1)
                    illegal_option(argv[i][j]);
            }
        }
    }
    return res;
}
