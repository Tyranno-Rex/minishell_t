# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 14:12:28 by minjinki          #+#    #+#              #
#    Updated: 2023/03/23 19:05:31 by minjinki         ###   ########.fr        #
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
				init_env\
				parse_env\
				val_utils

MAIN_DIR	=	src/MAIN/
MAIN_SRC	=	main

PARSE_DIR	=	src/PARSE/
PARSE_SRC	=	parse\
				quotes\
				spaces

UTILS_DIR	=	src/UTILS/
UTILS_SRC	=	error\
				free\
				linked_list

SRCS		=	$(addprefix $(ENV_DIR), $(addsuffix .c, $(ENV_SRC)))
SRCS		+=	$(addprefix $(MAIN_DIR), $(addsuffix .c, $(MAIN_SRC)))
SRCS		+=	$(addprefix $(PARSE_DIR), $(addsuffix .c, $(PARSE_SRC)))
SRCS		+=	$(addprefix $(UTILS_DIR), $(addsuffix .c, $(UTILS_SRC)))
OBJS		=	$(SRCS:%.c=%.o)

LIBFT		=	src/LIBFT/
LIBFT_LIB	=	$(LIBFT)libft.a

all			:	$(NAME)

$(NAME)		:	$(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(RL_LIB) $(LIBFT_LIB)

%.o			:	%c
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