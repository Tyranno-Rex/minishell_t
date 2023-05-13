/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_spaces.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:49:31 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/13 10:28:13 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	free_lst(t_token **tmp)
{
	ft_lstclear(tmp);
	ft_lstclear(&(g_glob.tok));
	return (FALSE);
}

t_bool	add_space(t_token **tmp)
{
	char	*s;
	t_token	*new;

	s = ft_strdup(" ");
	if (!s)
		return (FALSE);
	new = ft_lstnew(SPACES, s);
	if (!new)
		return (free_lst(tmp));
	ft_lstadd_back(tmp, new);
	return (TRUE);
}

t_bool	split_by_space(t_token **tmp, t_token *cur)
{
	int		start;
	int		len;
	char	*s;

	start = -1;
	while (cur->data[++start] && start < (int)ft_strlen(cur->data))
	{
		while (cur->data[start] && ft_is_space(cur->data[start]))
			start++;
		if (start > 0 && ft_is_space(cur->data[start - 1]))
			add_space(tmp);
		if (!(cur->data[start]))
			break ;
		len = ft_strnlen(&(cur->data[start]), ' ');
		s = ft_strndup(&(cur->data[start]), len);
		if (!s)
			return (free_lst(tmp));
		if (!ft_lstadd_back(tmp, ft_lstnew(STR, s)))
			return (free_lst(tmp));
		start += len;
	}
	if (ft_lstlast(*tmp)->type != SPACES && ft_is_space(cur->data[start - 1]))
		add_space(tmp);
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
				return (print_error("Fail to allocate memory\n"));
		}
		else
		{
			if (!add_quotes(&tmp, cur))
				return (print_error("Fail to allocate memory\n"));
		}
		cur = cur->next;
	}
	ft_lstclear(&(g_glob.tok));
	g_glob.tok = tmp;
	return (TRUE);
}
