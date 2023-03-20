/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:49:31 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/20 18:46:53 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	split_by_space(t_token *pre, t_token *cur)
{
	int		i;
	char	*matrix;
	t_token	*new;

	new = malloc_node();
	if (!new)
		return (FALSE);
	matrix = ft_split(cur->data, ' ');
	if (!matrix)
		return (print_error("Fail to allocate memory: ft_split()\n"));
	i = -1;
	while (matrix[++i])
	{
		new->data = ft_strdup(matrix[i]);
		// ft_lstinsert(pre, new, cur);
		free(matrix[i]);
	}
	return (TRUE);
}

void	deal_spaces(char *cmd)
{
	t_token	*cur;
	t_token	*pre;

	pre = NULL;
	cur = g_glob.tok;
	while (cur)
	{
		if (cur->type == STR)
		{
			split_by_space(pre, cur);
		}
		pre = cur;
		cur = cur->next;
	}
}
