NAME	=	uls
CFLG	=	-std=c11 -Wall -Wextra -Werror -Wpedantic -g
COMP	=	clang
SRCD	=	src
INCD	=	inc
OBJD	=	obj
LMXD	=	libmx
LMXA:=	$(LMXD)/libmx.a
LMXI:=	$(LMXD)/inc
INC		=	uls.h
INCS	=	$(addprefix $(INCD)/, $(INC))
SRC		=	main.c mx_check_flags.c mx_del_fils.c mx_del_litarr.c \
			mx_getname.c mx_indification_args.c mx_join.c \
			mx_make_new_list.c mx_opendir.c mx_output.c mx_parse.c \
			mx_sort_asci.c mx_out_menu.c mx_long_out.c \
			mx_check_dev.c mx_print.c mx_print_lnk.c mx_print_per.c \
			mx_get_user_name.c mx_print_sz.c mx_maj_min.c mx_edit_time.c \
			mx_print_symb.c mx_sort.c mx_one.c \
			mx_multicolumn.c mx_out_m.c mx_check_file.c
SRCS	=	$(addprefix $(SRCD)/, $(SRC))
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))
all: install clean
install: $(LMXA) $(NAME)
$(NAME): $(OBJS)
	@$(COMP) $(CFLG) $(OBJS) -L$(LMXD) -lmx -o $@
$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(COMP) $(CFLG) -c $< -o $@ -I$(INCD) -I$(LMXI)
$(OBJS): | $(OBJD)
$(OBJD):
	@mkdir -p $@
$(LMXA):
	@make -sC $(LMXD)
clean:
	@make -sC $(LMXD) $@
	@rm -rf $(OBJD)
uninstall: clean
	@make -sC $(LMXD) $@
	@rm -rf $(NAME)
reinstall: uninstall install
	@make -sC $(LMXD) $@
	@rm -rf $(OBJD)
compile:
	@$(COMP) $(CFLG) $(LMXA) $(SRCS) -o $(NAME) -I$(INCD) -I$(LMXI)
