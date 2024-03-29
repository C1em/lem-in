# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coremart <coremart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 17:33:24 by coremart          #+#    #+#              #
#    Updated: 2019/10/31 21:05:09 by coremart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##COMPILATION ##
NAME = lem-in
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security -fsanitize=undefined
CFLAGS = -g -Werror -Wall -Wextra -pedantic-errors -std=c99
DFLAGS = -MT $@ -MMD -MP -MF $(DDIR)/$*.d
AFLAGS =
ASAN =

## INCLUDES ##
LIB = libft
LIBH = $(LIB)/include
HDIR = include
LIBA = $(LIB)/libft.a

## SOURCES ##
SDIR = src
_SRCS = bonus.c check_duplicates.c edges_utils.c list_utils.c main.c make_graph.c \
max_flow.c parser.c parsing_list_utils.c paths.c printer.c q_sort_paths.c queue.c \
vertices_utils.c set_msg.c printer_tools.c parse_vertices.c free_all.c \
init_utils.c bfs.c dfs.c
SRCS = $(patsubst %,$(SDIR)/%,$(_SRCS))

## OBJECTS ##
ODIR = obj
_OBJS = $(_SRCS:.c=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

## DEPENDENCIES ##
DDIR = dep
_DEPS = $(_OBJS:.o=.d)
DEPS = $(patsubst %,$(DDIR)/%,$(_DEPS))

### RULES ###

all: $(NAME)

$(NAME): $(OBJS)
	@if [ "$(AFLAGS)" == "" ];\
	then\
		make -j 8 -C $(LIB);\
	else\
		make -j 8 -C $(LIB) asan;\
	fi
	gcc -o $(NAME) $(LIBA) $(OBJS) $(CFLAGS) $(AFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c
	gcc $(CFLAGS) $(DFLAGS) -o $@ -c $< -I $(HDIR) -I $(LIBH) $(AFLAGS)

-include $(DEPS)

clean:
	@make -j 8 -C $(LIB) clean
	@rm -f $(OBJS)

fclean: clean
	@make -j 8 -C $(LIB) fclean
	@rm -f $(NAME)
	@rm -rf $(NAME).dSYM

re: fclean all

asan: AFLAGS = $(ASANFLAGS)
asan: all

reasan: AFLAGS = $(ASANFLAGS)
reasan: re

.PRECIOUS: $(DDIR)/%.d
.PHONY: all clean fclean re $(NAME)
