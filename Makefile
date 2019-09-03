# ---------- #
# Debug mode #
# ---------- #

DEBUG = no

# --------- #
# Directory #
# --------- #

LIBDIR = libft/
PATHLIBDIR = libft/libs/
SRCDIR = srcs/
OBJDIR = objs/
INCDIR = includes/
INCLIBDIR = libft/includes/

VPATH = objs:\
		srcs

# ------------------ #
# Compiler and flags #
# ------------------ #

CC = cc
ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra -g3
else
	CFLAGS = -Wall -Wextra -Werror
endif
CPPFLAGS = -I $(INCDIR) -I $(INCLIBDIR)
LDLIBS = -lft
LDFLAGS = -L $(PATHLIBDIR)
LFLAGS = -lncurses

# --------------- #
# Different names #
# --------------- #

NAME = ft_ls

SRCS_NAMES = display.c\
						 error.c\
						 ft_ls.c\
						 insert.c\
						 list.c\
						 list_remove.c\
						 main.c\
						 open.c\
						 parser.c\
						 sort.c

OBJS_NAMES = $(SRCS_NAMES:.c=.o)
HEADERS_NAMES = ft_ls.h
LIBS_NAMES = libft.a

OBJ = $(addprefix $(OBJDIR), $(OBJS_NAMES))
HEADERS = $(addprefix $(INCDIR), $(HEADERS_NAMES))
LIBS = $(addprefix $(PATHLIBDIR), $(LIBS_NAMES))

# ----------------- #
# Command variables #
# ----------------- #

CREATE = mkdir -p
DEL = /bin/rm -rf
PRINT = printf
PHONY = all clean cleans fclean re libs cleanlibs fcleanlibs lldb norm help
REMOVE = "\r\033[K"
FUNC = "%-60b\r"

# PROGRESS BAR | Original author Cpirlot
T = $(words $(OBJ))
N = 0
C = $(words $N)$(eval N := x $N)
ECHO = "[`expr $C  '*' 100 / $T`%]"

# ----- #
# Rules #
# ----- #

all : libs $(NAME)

ifeq ($(DEBUG), yes)
	@$(PRINT) "Debug mode : on\n"
else
	@$(PRINT) "Debug mode : off\n"
endif

$(NAME) : $(LIBS) $(OBJS_NAMES)
	@$(CC) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS) $(LFLAGS) $(CFLAGS) $(CPPFLAGS)
	@$(PRINT) $(REMOVE)"Executable built\n"

libs :
	@$(MAKE) -j3 -C $(LIBDIR)

%.o : %.c $(HEADERS)
	@$(CREATE) $(OBJDIR)
	@$(CC) -o $(OBJDIR)$@ -c $< $(CFLAGS) $(CPPFLAGS)

clean : cleanlibs
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

cleans :
	@$(DEL) $(OBJDIR)
	@$(PRINT) ".o file deleted\n"

fclean : cleans fcleanlibs
	@$(DEL) $(NAME)
	@$(PRINT) "Executable destroyed\n"

cleanlibs :
	@$(MAKE) -C $(LIBDIR) clean

fcleanlibs :
	@$(MAKE) -C $(LIBDIR) fclean

lldb :
	@lldb ./$(NAME)

norm :
	@norminette ./$(NAME)

re : fclean all

help :
	@$(PRINT) "Rules available : all, clean, cleans, fclean, re, libs, cleanlibs, fcleanlibs, lldb, norm and help\n"

.PHONY : $(PHONY)
