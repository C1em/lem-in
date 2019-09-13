# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 17:33:24 by coremart          #+#    #+#              #
#    Updated: 2019/09/13 15:08:17 by cbenoit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##COMPILATION ##
NAME = lem-in
CFLAGS = -Werror -Wall -Wextra
DFLAGS = -MT $@ -MMD -MP -MF $(DDIR)/$*.d

## INCLUDES ##
LIB = libft
LIBH = $(LIB)/include
HDIR = include
LIBA = $(LIB)/libft.a

## SOURCES ##
SDIR = src
_SRCS = bonus.c check_duplicates.c edges_utils.c list_utils.c main.c make_graph.c \
max_flow.c parser.c parsing_list_utils.c paths.c printer.c q_sort_paths.c queue.c \
vertices_utils.c
SRCS = $(patsubst %,$(SDIR)/%,$(_SRCS))

## OBJECTS ##
ODIR = obj
_OBJS = $(_SRCS:.c=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

## DEPENDENCIES ##
DDIR = deps
_DEPS = $(_OBJS:.o=.d)
DEPS = $(patsubst %,$(DDIR)/%,$(_DEPS))

### RULES ###

all: $(NAME)

$(NAME): $(OBJS)
	make -j 8 -C $(LIB)
	gcc -g -o $(NAME) $(LIBA) $(OBJS) $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c
	gcc $(CFLAGS) -g $(DFLAGS) -o $@ -c $< -I $(HDIR) -I $(LIBH)

-include $(DEPS)

clean:
	@make -j 8 -C $(LIB) clean
	@rm -f $(OBJS)

fclean: clean
	@make -j 8 -C $(LIB) fclean
	@rm -f $(NAME)

re: fclean all

.PRECIOUS: $(DDIR)/%.d
.PHONY: all clean fclean re $(NAME)
