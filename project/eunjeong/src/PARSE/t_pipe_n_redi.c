/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe_n_redi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:29 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/13 10:22:46 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// 일반 문자열 노드 추가
t_bool	add_str(t_token **tmp, char *s, int len)
{
	t_token	*new;

	if (len < 1)
		return (TRUE);
	new = ft_lstnew(STR, ft_strndup(s, len));
	if (!new)
		return (FALSE);
	ft_lstadd_back(tmp, new);
	return (TRUE);
}

// 리다이렉션, 파이프 노드 추가
t_bool	add_redi_pipe(t_token **tmp, char *s, int len)
{
	int		i;
	char	c;
	t_token	*new;

	i = 0;
	c = *s;
	new = ft_lstnew(ERROR, NULL);
	if (!new)
		return (FALSE);
	while (++i < len)
	{
		if (s[i] != c)
		{
			new->data = ft_strndup(s, len);
			if (!(new->data))
				return (FALSE);
			ft_lstadd_back(tmp, new);
			return (TRUE);
		}
	}
	new->type = TMP;
	new->data = ft_strndup(s, len);
	ft_lstadd_back(tmp, new);
	return (TRUE);
}

t_bool	split_by_pipe_n_redi(t_token **tmp, t_token *cur)
{
	int		start;
	int		end;
	char	*pre;

	start = -1;
	pre = cur->data;
	while (cur->data[++start])
	{
		while (cur->data[start] && !ft_strchr("<|>", cur->data[start]))
			start++;
		if (!(cur->data[start]))
			return (add_str(tmp, pre, ft_strlen(pre)));
		end = start;
		while (cur->data[++end])
			if (!ft_strchr("<|>", cur->data[end]))
				break ;
		if (!add_str(tmp, pre, cur->data + start - pre))
			return (FALSE);
		if (!add_redi_pipe(tmp, cur->data + start, end - start))
			return (FALSE);
		start = end - 1;
		pre = cur->data + end;
	}
	return (TRUE);
}

t_bool	deal_pipe_n_redi(void)
{
	t_token	*cur;
	t_token	*tmp;

	tmp = NULL;
	cur = g_glob.tok;
	while (cur)
	{
		if (cur->type == STR)
		{
			if (!split_by_pipe_n_redi(&tmp, cur))
				return (print_error("Memory: deal_pipe_n_redi\n"));
		}
		else
		{
			if (!add_quotes(&tmp, cur))
				return (print_error("deal_pipe_n_redi\n"));
		}
		cur = cur->next;
	}
	ft_lstclear(&(g_glob.tok));
	g_glob.tok = tmp;
	return (TRUE);
}
