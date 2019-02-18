STR = ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcmp.c ft_strncmp.c \
	  ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
	  ft_strnstr.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
	  ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
	  ft_strtrim.c ft_strsplit.c ft_bzero.c ft_chr_index.c ft_strchr_exist.c \
	  ft_chrjoin_start.c ft_chrjoin_end.c ft_chrn_index.c ft_strsub_tab_fix.c \
	  ft_deplace.c ft_reverse_tablo.c

PRINTF = ft_printf.c \
		 parser.c \
		 gest_flag.c \
		 arg_s.c \
		 arg_n.c \
		 arg_convert.c \
		 arg_float.c \
		 apply_arg.c \
		 display.c \
		 tools.c \
		 tools_bis.c \
		 tools_apply_arg.c \
		 ft_itoa_other.c \
		 ft_itoa_other_u_s.c \
		 ft_convert_base.c \
		 binary.c \
		 manage_float.c \
		 apply_arg_float.c \
		 tools_float.c \
		 tools_n.c \
		 multiplication_float.c \
		 round_float.c \
		 add_float.c

PUT = ft_putstr.c ft_putnbr.c ft_putchar.c ft_putendl.c ft_putchar_fd.c \
	  ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

TO = ft_tolower.c ft_toupper.c ft_isspace.c

NB = ft_sqrt.c ft_atoi.c ft_itoa.c ft_numlen.c ft_pow_array_fix.c

GNL = get_next_line.c

IS = ft_isdigit.c ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isblank.c

MEM = ft_memset.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	  ft_memalloc.c ft_memdel.c

LST = ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c

SRC = $(STR) $(PUT) $(IS) $(MEM) $(LST) $(TO) $(NB) $(GNL) $(PRINTF)

DIRSRC = src

DIROBJ = obj

HEAD = libft.h

OBJ = $(SRC:%.c=$(DIROBJ)/%.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "ar rc: \033[32mOk\033[0m"
	@ranlib $(NAME)
	@echo "ranlib: \033[32mOk\033[0m"

$(DIROBJ)/%.o: $(DIRSRC)/%.c
	@gcc -o $@ -Wall -Werror -Wextra -c $<
	@echo "\033[36mlibft\033[0m $*: \033[32mOk\033[0m"

clean:
	@rm -f $(OBJ) $(EXEC)
	@echo "rm -f obj & $(EXEC): \033[33mOk\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "rm -f: \033[33mOk\033[0m"

re: fclean $(NAME)
