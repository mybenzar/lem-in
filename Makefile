# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/08 13:54:50 by mybenzar          #+#    #+#              #
#    Updated: 2019/09/08 16:05:02 by mybenzar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
LOGIN = `whoami`
CFLAGS = -Wall -Wextra -Werror -g3
NAME = lem-in
SRCDIR = ./srcs/
INCLDIR = ./includes/
LIBDIR = ./libft/
LIB = $(LIBDIR)libft.a
SRCS = parser.c \
		lemin.c \
		leave.c \
		check_and_fill_tree.c \
		check_part2.c \
		check_node_format.c \
		add_link_to_list.c \
		add_room_to_list.c \
		translate_list_to_string.c \
		convert_to_usefull.c \
		breadth_first_search.c \
		flow_optimizer.c \
		optimization.c \
		bfs_helper.c \
		display.c
ifdef SAN
	CFLAGS += -fsanitize=address,undefined
endif

vpath %.c $(SRCDIR)
OBJ = $(patsubst %.c, $(OBJS_DIR)%.o, $(SRCS))
OBJS_DIR = ./objs/

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJ) $(LIB)
	$(CC) $(CFLAGS) -I $(INCLDIR) $(OBJ) -o $@ -L $(LIBDIR) -lft
	echo "\n\033[36mCreation :\033[0m \033[35;4m$(NAME)\033[0m\n"

$(OBJ): $(OBJS_DIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -I $(INCLDIR) -o $@
	echo "\033[36mCompilation :\033[0m \033[32m$*\033[0m"

$(OBJS_DIR):
		mkdir $@

$(LIB): FORCE
	echo "\n\033[36mLibs Compilation :\033[0m \033[33m$(LIBDIR)\033[0m\n"
	make -C libft

FORCE:

clean :
	rm -rf $(OBJS_DIR)
	echo "\n\033[36mDeletion :\033[0m \033[32mObjects\033[0m\n"

cm : clean all

fclean : clean
	rm -rf $(NAME)
	make -C libft/ fclean
	echo "\033[36mDeletion :\033[0m \033[35;4m$(NAME)\033[0m\n"

re : fclean all

.SILENT :
.PHONY : all clean fclean re cm
