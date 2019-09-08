CC = clang
LOGIN = `whoami`
CFLAGS = -Wall -Wextra -Werror -g3
NAME = lem-in
SRCDIR = ./srcs/
INCLDIR = ./includes/
LIBDIR = ./libft/
LIB = $(LIBDIR)libft.a
SRCS = $(SRCDIR)parser.c \
		$(SRCDIR)lemin.c \
		$(SRCDIR)leave.c \
		$(SRCDIR)check_and_fill_tree.c \
		$(SRCDIR)check_part2.c \
		$(SRCDIR)check_node_format.c \
		$(SRCDIR)add_link_to_list.c \
		$(SRCDIR)add_room_to_list.c \
		$(SRCDIR)translate_list_to_string.c \
		$(SRCDIR)convert_to_usefull.c \
		$(SRCDIR)breadth_first_search.c \
		$(SRCDIR)flow_optimizer.c \
		$(SRCDIR)optimization.c \
		$(SRCDIR)bfs_helper.c \
		$(SRCDIR)display.c
OBJ = $(notdir $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJ) $(LIB)
	@$(CC) $(CFLAGS) -I $(INCLDIR) $^ -o $@ -L $(LIBDIR) -lft
	@echo "\n\033[36mCreation :\033[0m \033[35;4m$(NAME)\033[0m\n"

%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $^ -I $(INCLDIR)
	@echo "\033[36mCompilation :\033[0m \033[32m$*\033[0m"

$(LIB) :
	@echo "\n\033[36mLibs Compilation :\033[0m \033[33m$(LIBDIR)\033[0m\n"
	@make -C libft

clean :
	@rm -rf $(OBJ)
	@echo "\n\033[36mDeletion :\033[0m \033[32mObjects\033[0m\n"

cm : clean all

fclean : clean
	@rm -rf $(NAME)
	@make -C libft/ fclean
	@echo "\033[36mDeletion :\033[0m \033[35;4m$(NAME)\033[0m\n"

re : fclean all

.PHONY : all clean fclean re cm
