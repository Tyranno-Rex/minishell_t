# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 14:12:28 by minjinki          #+#    #+#              #
#    Updated: 2023/05/04 14:38:25 by minjinki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-g -Wall -Wextra -Werror
RM			=	rm -f
AR			=	ar
ARFLAGS		=	src

NAME		=	minishell

INCLUDE		=	include

RL_LIB		=	-lreadline -L${HOME}/.brew/opt/readline/lib
RL_INC		=	-I${HOME}/.brew/opt/readline/include

ENV_DIR		=	src/ENV/
ENV_SRC		=	env_utils\
				env_utils2\
				deal_env\
				init_env\
				parse_env

MAIN_DIR	=	src/MAIN/
MAIN_SRC	=	main\
				block\
				redirect_parse
				# single_builtin
				# single_redirect

PARSE_DIR	=	src/PARSE/
PARSE_SRC	=	parse\
				t_quotes\
				t_spaces\
				t_pipe_n_redi\
				t_set_pipe_n_redi\
				t_check_cmd\
				t_syntax_error\
				t_merge_n_split_nodes

UTILS_DIR	=	src/UTILS/
UTILS_SRC	=	error\
				free

SIGNAL_DIR	=	src/SIGNAL/
SIGNAL_SRC	=	signal\
				signal_2\
				signal_utils

BUILTIN_DIR =	src/BUILTIN/
BUILTIN_SRC	=   builtin\
				builtin_exec\
				pwd\
				echo\
				exit\
				env\
				cd\
				export\
				exec\
				unset

# 이거 왜 안되지..?
PIPE_DIR	=	src/PIPE/
PIPE_SRC	=	make_env2D\
				redir_fd\
				create_child\


SRCS		=	$(addprefix $(ENV_DIR), $(addsuffix .c, $(ENV_SRC)))
SRCS		+=	$(addprefix $(MAIN_DIR), $(addsuffix .c, $(MAIN_SRC)))
SRCS		+=	$(addprefix $(PARSE_DIR), $(addsuffix .c, $(PARSE_SRC)))
SRCS		+=	$(addprefix $(UTILS_DIR), $(addsuffix .c, $(UTILS_SRC)))
SRCS		+=  $(addprefix $(SIGNAL_DIR), $(addsuffix .c, $(SIGNAL_SRC)))
SRCS		+=  $(addprefix $(BUILTIN_DIR), $(addsuffix .c, $(BUILTIN_SRC)))
SRCS		+=  $(addprefix $(PIPE_DIR), $(addsuffix .c, $(PIPE_SRC)))

OBJS		=	$(SRCS:%.c=%.o)

LIBFT		=	src/LIBFT/
LIBFT_LIB	=	$(LIBFT)libft.a

all			:	$(NAME)

$(NAME)		:	$(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(RL_LIB) $(LIBFT_LIB)

%.o			:	%.c
	$(CC) $(CFLAGS) -I$(INCLUDE) $(RL_INC) -c $< -o $@

clean		:
	$(MAKE) -C $(LIBFT) clean
	$(RM) $(OBJS)

fclean		:	clean
	$(MAKE) -C $(LIBFT) fclean
	$(RM) $(NAME)

re			:
	$(MAKE) fclean
	$(MAKE) all

.PHONY		:	all clean fclean re