NAME = minishell

SRCDIR = ./main/
SRCS = $(addprefix $(SRCDIR), builtin_exec.c builtin.c pwd.c exit.c echo.c cd.c env.c main.c)

OBJS = $(SRCS:.c=.o)

COMPILER = cc
# CFLAGS = -Wall -Werror -Wextra
CFLAGS =

all: extern $(NAME)

extern:
	make -C lib/

$(NAME): $(OBJS)
	$(COMPILER) -o $(NAME) $(OBJS) lib/libft.a

$(SRCDIR)%.o: $(SRCDIR)%.c ./inc/minishell.h
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	make clean -C lib/
	rm -rf $(OBJS)

fclean: clean
	make fclean -C lib/
	rm -rf $(NAME)

re: fclean all

.PHONY: all extern clean fclean re
