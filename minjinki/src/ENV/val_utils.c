/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:31:05 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/23 19:10:04 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_val	*val_lstnew(char *val)
{
	t_val	*new;

	new = ft_calloc(1, sizeof(t_val));
	if (!new)
		return (NULL);
	new->val = val;
	return (new);
}

t_val	*val_lstlast(t_val *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	val_lstadd_back(t_env *env, t_val *new)
{
	if (!(env->val))
		env->val = new;
	else
		val_lstlast(env->val)->next = new;
}

void	val_lstclear(t_val **val)
{
	t_val	*tmp;

	while (*val)
	{
		tmp = (*val)->next;
		free((*val)->val);
	}
}
