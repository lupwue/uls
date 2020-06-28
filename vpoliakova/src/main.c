#include "uls.h"

int main(int argc, char *argv[]) {
    t_head head;

    mx_memset(&head, 0, sizeof(t_head)); 
    head.flags = (int *)malloc(sizeof(int) * mx_strlen(MY_FLAGS)); 
    mx_memset(head.flags, 0, mx_strlen(MY_FLAGS) * sizeof(int));
    head.count_flags = head.count_flags + mx_check_flags(argc, argv, &head);
    mx_parse(argc, argv, &head);
    if (head.ex > 0)
        exit(1);
return 0;
}

