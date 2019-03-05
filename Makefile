SRC = main.c \
	  open.c \
	  list.c \
	  sort.c \
	  ft_ls.c \
	  error.c \
	  parser.c \
	  insert.c \
	  display.c \
	  list_remove.c

DIRSRC = src

DIROBJ = obj

HEAD = ft_ls.h

LIBRARY = -L./libft -lft

NAME = ft_ls

OBJ = $(SRC:%.c=$(DIROBJ)/%.o)

FLAG = -Wall -Wextra

DEBUG = -g3

MKDIR = mkdir -p

all: directories $(NAME)

directories:
	@$(MKDIR) obj

$(NAME): $(OBJ)
	@make -C libft
	@gcc $(FLAG) $(DEBUG) $(OBJ) -o $(NAME) $(LIBRARY)


$(DIROBJ)/%.o: $(DIRSRC)/%.c
	@gcc -o $@ $(FLAG) $(DEBUG) -c $<
	@echo "\033[36mft_ls\033[0m $*: \033[32mOk\033[0m"

clean:
	@make -C libft clean
	@rm -f $(OBJ) $(EXEC)
	@echo "rm -f obj & $(EXEC): \033[33mOk\033[0m"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "rm -f: \033[33mOk\033[0m"

re: fclean $(NAME)
