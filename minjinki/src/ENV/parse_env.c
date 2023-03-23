/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:57:08 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/23 19:20:52 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	add_path_val(t_env *env, char *path)
{
	t_val	*new;

	new = val_lstnew(path);
	if (!new)
		return (FALSE);
	new->val = path;
	val_lstadd_back(env, new);
	return (TRUE);
}

t_bool	parse_path(char *key, char *p)
{
	int		i;
	char	**path;
	t_env	*new;

	new = env_lstnew(key);
	if (!new)
		return (FALSE);
	new->key = key;
	path = ft_split(p, ':');
	if (!path)
		return (FALSE);
	i = -1;
	while (path[++i])
	{
		if (!add_path_val(new, path[i]))
			return (FALSE);
	}
	return (TRUE);
}

t_bool	make_envnode(char *key, char *val)
{
	t_env	*new;
	t_val	*value;

	new = env_lstnew(key);
	if (!new)
		return (FALSE);
	value = val_lstnew(val);
	if (!value)
		return (FALSE);
	new->val = value;
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
	if (!ft_strcmp("PATH", key))
		parse_path(key, v);
	else
	{
		val = ft_strdup(v);
		if (!val)
		{
			free(key);
			return (FALSE);
		}
		if (!make_envnode(key, val))
			return (FALSE);
	}
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
	env_lstprint();
	return (TRUE);
}
