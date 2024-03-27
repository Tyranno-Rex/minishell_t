/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:25:32 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/11 15:46:54 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_with_code(const char *s, int error)
{
	ft_putstr_fd(s, 2);
	exit(error);
}

int	print_error(const char *s, int error)
{
	ft_putstr_fd(s, 2);
	return (error);
}
