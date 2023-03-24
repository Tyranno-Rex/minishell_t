/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:57:08 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/23 19:28:28 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	parse_path(void)
{
	char	**path;

	path = ft_split(get_env("PATH"), ':');
	if (!path)
		return (print_error("Fail to allocate memory: parse_path\n"));
	g_glob.path = path;
	return (TRUE);
}

t_bool	make_envnode(char *key, char *val)
{
	t_env	*new;

	new = env_lstnew(key, val);
	if (!new)
		return (FALSE);
	env_lstadd_back(&(g_glob.env), new);
	return (TRUE);
}

t_bool	env_list(char *k, char *v)
{
	char	*key;
	char	*val;

	key = ft_strdup(k);
	if (!key)
		return (FALSE);
	val = ft_strdup(v);
	if (!val)
	{
		free(key);
		return (FALSE);
	}
	if (!make_envnode(key, val))
		return (FALSE);
	return (TRUE);
}

t_bool	parse_env(char ***env)
{
	int		i;
	char	**kv;

	i = -1;
	while ((*env)[++i])
	{
		kv = ft_split((*env)[i], '=');
		if (!kv)
			return (print_error("Fail to allocate memory: parse_env\n"));
		if (!env_list(kv[0], kv[1]))
		{
			env_lstclear(&(g_glob.env));
			return (print_error("Fail to allocate memory: env list\n"));
		}
		free_matrix(kv);
	}
	if (!parse_path())
		return (FALSE);
	env_lstprint(); /*** remove ***/
	return (TRUE);
}
