NAME = minishell_pipe

SRCDIR =
SRCS = $(addprefix $(SRCDIR), signal.c)

OBJS = $(SRCS:.c=.o)

COMPILER = cc
# CFLAGS = -Wall -Werror -Wextra
CFLAGS =

all: extern $(NAME)

extern:
	make -C ../libft/

$(NAME): $(OBJS)
	$(COMPILER) -o $(NAME) $(OBJS) ../libft/libft.a

$(SRCDIR)%.o: $(SRCDIR)%.c ../inc/minishell.h
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ../libft/
	rm -rf $(OBJS)

fclean: clean
	make fclean -C ../libft/
	rm -rf $(NAME)

re: fclean all

.PHONY: all extern clean fclean re
