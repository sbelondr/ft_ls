STR = ft_printf.c \
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
	  tools_float_bis.c \
	  ft_itoa_other.c \
	  ft_itoa_other_u_s.c \
	  ft_convert_base.c \
	  binary.c \
	  manage_float.c \
	  apply_arg_float.c \
	  tools_float.c \
	  multiplication_float.c \
	  add_float.c \
	  apply_arg_s.c \
	  apply_arg_n.c \
	  apply_arg_convert.c

FILE = $(STR)

DIROBJ = ../../obj

NAME = libftprintf.a

OBJ = $(FILE:%.c=$(DIROBJ)/%.o)

FLAGS = -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[32mMake ok\033[0m"

$(DIROBJ)/%.o: %.c
	@gcc $< $(FLAGS) -c -o $@
	@echo "\033[36mft_printf\033[0m $*: \033[32mOk\033[0m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
.SILENT: all $(NAME) clean fclean re
