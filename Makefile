# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/29 15:27:06 by cbenoit           #+#    #+#              #
#    Updated: 2019/09/10 16:21:47 by cbenoit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in
CC		=	clang
CFLAGS	=	-Werror -Wextra -Wall
LIB_DIR	=	libft/
LIB		=	$(LIB_DIR)libft.a
OBJ		=	$(SRC:.c=.o)
SRC		=	src/main.c src/check_duplicates.c src/check_graph.c src/edges_utils.c \
			src/error.c src/list_utils.c src/make_graph.c \
			src/max_flow.c src/parser.c src/parsing_list_utils.c \
			src/paths.c src/printer.c src/q_sort_paths.c src/queue.c \
			src/vertices_utils.c \

all:		$(NAME)
$(NAME):	$(OBJ)
			@make -j 8 -C $(LIB_DIR)
			@make -j 8 -C $(LIB_DIR)
			$(CC) $(CFLAGS) -Iinclude -o $(NAME) $(OBJ) $(LIB)
clean:
			@make -j 8 -C $(LIB_DIR) clean
			rm -f $(OBJ)
fclean:		clean
			@make -j 8 -C $(LIB_DIR) fclean
			rm -f $(NAME)
re:			fclean all
