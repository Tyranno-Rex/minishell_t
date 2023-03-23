/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:16:58 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/23 19:14:56 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_lstprint(void)
{
	t_env	*cur;
	t_val	*val;

	cur = g_glob.env;
	while (cur)
	{
		printf("key: %s\n", cur->key);
		val = cur->val;
		while (val)
		{
			printf("val: %s\n", val->val);
			val = val->next;
		}
		printf("--------------------------------------\n");
		cur = cur->next;
	}
}

t_env	*env_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	else if (!*lst)
		*lst = new;
	else
		env_lstlast(*lst)->next = new;
}

t_env	*env_lstnew(char *key)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	return (new);
}

t_bool	env_lstclear(t_env **lst)
{
	t_env	*tmp;

	if (!lst)
		return (TRUE);
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->key);
		val_lstclear(&((*lst)->val));
	}
	return (FALSE);
}
