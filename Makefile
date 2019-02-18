SRC = ft_ls.c \
	  open.c \
	  error.c \
	  display.c \
	  sort.c

DIROBJ = obj

HEAD = ft_ls.h

LIBRARY = -L./libft -lft

NAME = ft_ls

OBJ = $(SRC:%.c=$(DIROBJ)/%.o)

FLAG = -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAG) $(OBJ) -o $(NAME) $(LIBRARY)


$(DIROBJ)/%.o: %.c
	@gcc -o $@ $(FLAG) -c $<
	@echo "\033[36mlibft\033[0m $*: \033[32mOk\033[0m"

clean:
	@rm -f $(OBJ) $(EXEC)
	@echo "rm -f obj & $(EXEC): \033[33mOk\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "rm -f: \033[33mOk\033[0m"

re: fclean $(NAME)
