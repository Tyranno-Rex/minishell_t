/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:35:17 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/28 17:04:23 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	add_oldpath(t_env *env)
{
	char	*pwd;
	t_env	*new;

	pwd = NULL;
	new = env_lstnew("OLDPWD", NULL);
	if (!new)
		return (FALSE);
	new->val = getcwd(pwd, 0);
	env_lstadd_back(&env, new);
	return (TRUE);
}

void	print_env(char ***env)
{
	int	i;

	i = -1;
	while ((*env)[++i])
		printf("%s\n", (*env)[i]);
	printf("\n\n");
}

t_bool	copy_env(char ***env)
{
	int	matrix;
	int	len;
	int	i;

	matrix = ft_matrixlen(*env);
	g_glob.env_ori = ft_calloc(matrix + 1, sizeof(char *));
	if (!(g_glob.env_ori))
		return (print_error("Fail to allocate memory: g_glob.env_ori\n"));
	i = -1;
	while (++i < matrix)
	{
		len = ft_strlen((*env)[i]);
		g_glob.env_ori[i] = ft_calloc(len + 1, sizeof(char));
		if (!(g_glob.env_ori[i]))
		{
			free_matrix(g_glob.env_ori);
			return (print_error("Fail to allocate memory: g_glob.env_ori[i]\n"));
		}
		ft_strlcpy(g_glob.env_ori[i], (*env)[i], len + 1);
	}
	return (TRUE);
}

t_bool	init_env(char ***env)
{
	if (!copy_env(env))
		return (FALSE);
	if (!parse_env(&(g_glob.env_ori)))
		return (FALSE);
	if (!add_oldpath(g_glob.env))
		return (FALSE);
	return (TRUE);
}
