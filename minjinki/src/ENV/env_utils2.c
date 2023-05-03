/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MJKim <zinnnn37@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:40:46 by MJKim             #+#    #+#             */
/*   Updated: 2023/03/24 13:40:46 by MJKim            ###   ########.fr       */
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
