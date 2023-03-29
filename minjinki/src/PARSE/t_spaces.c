/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_spaces.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:49:31 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/28 17:11:34 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	free_lst(t_token **tmp)
{
	ft_lstclear(tmp);
	ft_lstclear(&(g_glob.tok));
	return (FALSE);
}

t_bool	split_by_space(t_token **tmp, t_token *cur)
{
	int		start;
	int		len;
	char	*s;
	t_token	*new;

	start = -1;
	while (cur->data[++start])
	{
		while (cur->data[start] && ft_is_space(cur->data[start]))
			start++;
		if (!(cur->data[start]))
			break ;
		len = ft_strnlen(&(cur->data[start]), ' ');
		s = ft_strndup(&(cur->data[start]), len);
		if (!s)
			return (free_lst(tmp));
		new = ft_lstnew(STR, s);
		if (!new)
			return (free_lst(tmp));
		ft_lstadd_back(tmp, new);
		start += len;
	}
	return (TRUE);
}

t_bool	add_quotes(t_token **tmp, t_token *cur)
{
	char	*s;
	t_token	*new;

	new = malloc_node();
	if (!new)
	{
		ft_lstclear(tmp);
		return (FALSE);
	}
	new->type = cur->type;
	s = ft_strdup(cur->data);
	if (!s)
		return (free_lst(tmp));
	new->data = s;
	ft_lstadd_back(tmp, new);
	return (TRUE);
}

t_bool	deal_spaces(void)
{
	t_token	*cur;
	t_token	*tmp;

	tmp = NULL;
	cur = g_glob.tok;
	while (cur)
	{
		if (cur->type == STR)
		{
			if (!split_by_space(&tmp, cur))
				return (print_error("Fail to allocate memory: split_by_spaces()\n"));
		}
		else
		{
			if (!add_quotes(&tmp, cur))
				return (print_error("Fail to allocate memory: split_by_spaces()\n"));
		}
		cur = cur->next;
	}
	ft_lstclear(&(g_glob.tok));
	g_glob.tok = tmp;
	return (TRUE);
}
