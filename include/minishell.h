/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:02:08 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/11 18:01:37 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include "libft.h"
# include "parse.h"
# include "struct.h"
# include "utils.h"

# define SUCCESS 0
# define FAILURE 1
# define TRUE 1
# define FALSE 0

t_data	g_data;

/******************	minishell.c	******************/
int	minishell(void);

#endif