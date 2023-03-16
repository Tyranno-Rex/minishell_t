/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:35:17 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/16 14:37:36 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(char ***env)
{
	int	i;

	i = -1;
	while ((*env)[++i])
		printf("%s\n", (*env)[i]);
	printf("\n\n");
}

/*
** 초기 세팅이라 exit() 사용
*/
t_bool	copy_env(char ***env)
{
	int	matrix;
	int	len;
	int	i;

	matrix = ft_matrixlen(*env);
	g_glob.env = ft_calloc(matrix + 1, sizeof(char *));
	if (!(g_glob.env))
		return (print_error("Fail to allocate memory: g_glob.env\n"));
	i = -1;
	while (++i < matrix)
	{
		len = ft_strlen((*env)[i]);
		g_glob.env[i] = ft_calloc(len + 1, sizeof(char));
		if (!(g_glob.env[i]))
		{
			free_matrix(g_glob.env);
			return (print_error("Fail to allocate memory: g_glob.env[i\n"));
		}
		ft_strlcpy(g_glob.env[i], (*env)[i], len + 1);
		printf("%s\n", g_glob.env[i]);
	}
	return (TRUE);
}
