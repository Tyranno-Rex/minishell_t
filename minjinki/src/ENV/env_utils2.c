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

t_env	*search_key(char *key)
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
