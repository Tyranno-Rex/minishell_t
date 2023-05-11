/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:00:15 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/11 16:41:37 by minjinki         ###   ########.fr       */
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
{	// 2차원 배열 해제
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
	// tree free(만든다면..)
}

t_bool	free_all(void)
{	// 전역변수에 메모리 할당하는 변수 있으면 여기 추가
	if (g_glob.cmd)
		free_cmd(g_glob.cmd);
	if (g_glob.env_ori)
		free_matrix(g_glob.env_ori);
	if (g_glob.path)
		free_matrix(g_glob.path);
	// if (g_glob.env)
	// 	env_lstclear(&(g_glob.env));
	return (FALSE);
}
