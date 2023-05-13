/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:00:15 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/13 10:25:35 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	ft_free(void *av)
{
	if (av)
		free(av);
	return (FALSE);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (matrix)
	{
		while (matrix[++i])
		{
			free(matrix[i]);
			matrix[i] = NULL;
		}
		free(matrix);
		matrix = NULL;
	}
}

void	free_cmd(char *cmd)
{
	if (cmd)
		free(cmd);
	if (&(g_glob.tok))
		ft_lstclear(&(g_glob.tok));
}

t_bool	free_all(void)
{
	if (g_glob.cmd)
		free_cmd(g_glob.cmd);
	if (g_glob.env_ori)
		free_matrix(g_glob.env_ori);
	if (g_glob.path)
		free_matrix(g_glob.path);
	return (FALSE);
}
