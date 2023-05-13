/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_print_tree2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:44:50 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/02 14:49:30 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_pipe(t_pipe *pipe)
{
	if (pipe)
	{
		printf("fd: %d, %d\n", pipe->fd[0], pipe->fd[1]);
		print_cmd(pipe->cmd);
		print_pipe(pipe->pipe);
		printf("-------------------------------\n");
	}
}
