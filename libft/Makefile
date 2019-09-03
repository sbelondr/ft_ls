# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/21 14:49:02 by sbelondr          #+#    #+#              #
#    Updated: 2019/08/21 12:33:15 by sbelondr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG = no

# Directory
SRCDIR = srcs/
OBJDIR = objs/
INCDIR = includes/
LIBDIR = libs/

VPATH = .:\
	objs:\
	srcs:\
	srcs/array:\
	srcs/char:\
	srcs/file:\
	srcs/ft_printf:\
	srcs/lst:\
	srcs/mem:\
	srcs/num:\
	srcs/put:\
	srcs/str:\

# Compiler and flags
CC = gcc

ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra -g3
else
	CFLAGS = -Wall -Werror -Wextra
endif

CPPFLAGS = -I $(INCDIR)

LDFLAGS = 

# Files

NAME = $(LIBDIR)libft.a

FT_PRINTF = ft_printf.c	parser.c gest_flag.c arg_s.c arg_n.c arg_convert.c arg_float.c\
	apply_arg.c	display.c tools.c tools_bis.c tools_float_bis.c ft_itoa_other.c\
	ft_itoa_other_u_s.c ft_convert_base.c binary.c manage_float.c apply_arg_float.c\
	tools_float.c multiplication_float.c add_float.c apply_arg_s.c apply_arg_n.c\
	apply_arg_convert.c prepare.c

SRCS_NAMES = ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcmp.c ft_strncmp.c\
	ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c\
	ft_strnstr.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c\
	ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c\
	ft_strtrim.c ft_strsplit.c ft_bzero.c ft_chr_index.c ft_strchr_exist.c\
	ft_chrjoin_start.c ft_chrjoin_end.c ft_chrn_index.c ft_strsub_tab_fix.c\
	ft_deplace.c ft_reverse_tablo.c ft_cnt_chr.c ft_strdeldup.c ft_lastchr.c\
	ft_arraydup.c ft_arraydel.c ft_arraydelline.c ft_arraylen.c ft_arraydisplay.c\
	ft_arrayjoin.c ft_arraysub.c ft_putstr.c ft_putnbr.c ft_putchar.c\
	ft_putendl.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	ft_tolower.c ft_toupper.c ft_isspace.c ft_sqrt.c ft_atoi.c ft_itoa.c\
	ft_numlen.c ft_pow_array_fix.c get_next_line.c get_end_line.c ft_isdigit.c\
	ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isblank.c ft_memset.c\
	ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c\
	ft_memdel.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c\
	ft_lstmap.c $(FT_PRINTF)

OBJS_NAMES = $(SRCS_NAMES:.c=.o)
	HEADERS_NAMES = libft.h ft_printf.h

SRC = $(addprefix $(SRCDIR), $(SRCS_NAMES))
OBJ = $(addprefix $(OBJDIR), $(OBJS_NAMES))
HEADERS = $(addprefix $(INCDIR), $(HEADERS_NAMES))

# Commands variables

AR = ar
ARFLAGS = rc
SORT = ranlib
CREATE = mkdir -p
DEL = /bin/rm -rf
PRINT = printf
PHONY = all clean fclean re norm help

# Color

RED = \033[31m
GREEN = \033[32m
BLUE = \033[36m
CLOSE = \033[0m

# Progress & display
SHELL = bash
compteur = 0
display_mode = 0
TOTAL = `find srcs -type f | cut -d '/' -f 3 | wc -l | cut -d ' ' -f 6`
ADD_VAL = $(eval compteur=$(shell echo $$(($(compteur)+1))))
ADD_VAL_DYSPLAY = $(eval display_mode=$(shell echo $$(($(display_mode)+1))))

# Rules

all: verif $(NAME)
	@$(PRINT) "$(BLUE)libft$(CLOSE): built -> $(GREEN)Ok$(CLOSE)\n"

verif:
ifeq ($(display_mode), 0)
ifeq ($(DEBUG), yes)
	@$(PRINT) " $(RED)Mode debug$(CLOSE)\n"
else
	@$(PRINT) " $(GREEN)Mode standard$(CLOSE)\n"
endif
endif

$(NAME): $(OBJS_NAMES)
	@$(PRINT) "\n"
	@$(CREATE) $(LIBDIR)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@$(SORT) $(NAME)

%.o : %.c $(HEADERS)
	@$(CREATE) $(OBJDIR)
	$(ADD_VAL)
	@$(CC) -o $(OBJDIR)$@ -c $< $(CFLAGS) $(CPPFLAGS)
	@echo -ne "$(BLUE)libft$(CLOSE): compil $(compteur)/$(TOTAL)     "\\r

clean : verif
	@$(DEL) $(OBJDIR)
	@$(PRINT) "$(BLUE)libft$(CLOSE): clean -> $(GREEN)Ok$(CLOSE)\n"

fclean: verif clean
	@$(DEL) $(LIBDIR)
	@$(PRINT) "$(BLUE)libft$(CLOSE): fclean -> $(GREEN)Ok$(CLOSE)\n"

re: fclean all

norm:
	@norminette **/*.[ch]
	@norminette **/*/*.[ch]

help:
	@$(PRINT) "$(BLUE)libft$(CLOSE): Rules available: all, clean, fclean, re, norm and help\n"

.PHONY: $(PHONY)
