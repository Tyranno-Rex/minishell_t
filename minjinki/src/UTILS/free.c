/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:00:15 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/23 17:12:50 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;
}

void	free_cmd(char *cmd)
{
	if (cmd)
		free(cmd);
	if (&(g_glob.tok))
		ft_lstclear(&(g_glob.tok));
}

void	free_all(void)
{
	if (g_glob.cmd)
		free_cmd(g_glob.cmd);
	if (g_glob.env_ori)
		free_matrix(g_glob.env_ori);
	if (g_glob.path)
		free_matrix(g_glob.path);
	if (g_glob.env)
		env_lstclear(g_glob.env);
}
