/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:22:06 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/13 10:23:37 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_with_code(char *s, int errno)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	exit(errno);
}

t_bool	print_error(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	return (FALSE);
}

t_bool	print_syntax_error(char *s)
{
	printf("minishell: syntax error near unexpected token '%s'\n", s);
	g_glob.exit_stat = 258;
	return (FALSE);
}
