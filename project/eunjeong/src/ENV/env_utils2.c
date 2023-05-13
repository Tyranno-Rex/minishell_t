/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:40:46 by MJKim             #+#    #+#             */
/*   Updated: 2023/05/13 10:28:59 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*env_search_key(char *key)
{
	t_env	*cur;

	cur = g_glob.env;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void	env_free_one(t_env *env)
{
	if (env)
	{
		if (env->key)
		{
			free(env->key);
			env->key = NULL;
		}
		if (env->val)
		{
			free(env->val);
			env->val = NULL;
		}
		free(env);
		env = NULL;
	}
}

void	env_remove(t_env *pre, t_env *del)
{
	t_env	*tmp;

	tmp = del;
	if (pre)
		printf("pre: %s\n", pre->key);
	printf("del: %s\n", del->key);
	if (!pre)
		g_glob.env = tmp->next;
	else
		pre->next = del->next;
	env_free_one(tmp);
}
