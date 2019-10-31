# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbenoit <cbenoit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 11:46:04 by coremart          #+#    #+#              #
#    Updated: 2019/10/31 23:30:08 by coremart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## COMPILATION ##
NAME = libft.a
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security -fsanitize=undefined
CFLAGS = -g -Wall -Wextra -Werror -pedantic-errors -std=c99
DFLAGS = -MT $@ -MMD -MP -MF $(DDIR)/$*.d
ASAN =

## INCLUDE ##
HDIR = include

## SOURCES ##
SDIR = src
_SRCS = ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memset.c ft_bzero.c \
ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c \
ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putnbr.c \
ft_putendl.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
ft_lstlen.c ft_lstdup.c ft_lstprint.c ft_strdiff.c ft_strndup.c ft_min.c \
ft_strclen.c ft_count_digit.c ft_memdup.c ft_absolute.c ft_memswap.c \
get_next_line.c ft_count_digitbase.c ft_print_byte.c ft_putbfloat.c \
ft_putnchar.c ft_putnstr.c ft_pwr.c ft_quicksort.c ft_ceil.c ft_isspace.c \
ft_isint.c ft_atoibase.c ft_convert_base.c ft_itoabase.c ft_ctabdel.c \
ft_lstappend.c ft_lstdel_cnt.c
SRCS = $(patsubst %,$(SDIR)/%,$(_SRCS))

## OBJECTS ##
ODIR = obj
_OBJS = $(_SRCS:.c=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

## DEPENDENCIES ##
DDIR = dep
_DEPS = $(_OBJS:.o=.d)
DEPS = $(patsubst %,$(DDIR)/%,$(_DEPS))

## RULES ##

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(ODIR)/%.o: $(SDIR)/%.c
	gcc $(CFLAGS) $(DFLAGS) -o $@ -c $< -I $(HDIR) $(ASAN)

-include $(DEPS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

asan: ASAN = $(ASANFLAGS)
asan: all

reasan: ASAN = $(ASANFLAGS)
reasan: re

.PRECIOUS: $(DDIR)/%.d
.PHONY: all clean fclean re $(NAME)
