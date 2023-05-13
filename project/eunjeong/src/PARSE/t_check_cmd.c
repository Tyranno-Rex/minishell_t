/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_check_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:04:38 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/13 10:23:49 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	check_valid4(t_token *cur)
{
	char	*s;

	s = cur->data;
	if (ft_strcmp(s, "|") == 0 || ft_strncmp(s, "<", 1) == 0
		|| ft_strncmp(s, ">", 1) == 0)
		return (print_syntax_error("newline"));
	return (TRUE);
}

t_bool	check_valid3(t_token *cur, t_token *nxt)
{
	char	*c;
	char	*n;
	t_token	*nnext;

	c = cur->data;
	n = nxt->data;
	nnext = nxt->next;
	while (nnext && nnext->type == SPACES)
		nnext = nnext->next;
	if (!nxt)
		n = NULL;
	if ((ft_strcmp(c, "|") == 0 && ft_strncmp(n, ">", 1) == 0)
		|| (ft_strcmp(c, "|") == 0 && ft_strcmp(n, "|") == 0)
		|| (ft_strcmp(c, ">") == 0 && ft_strcmp(n, "|") == 0)
		|| (ft_strcmp(c, ">>") == 0 && ft_strcmp(n, "|") == 0)
		|| (ft_strcmp(c, "<") == 0 && ft_strcmp(n, "|") == 0)
		|| (ft_strcmp(c, "<<") == 0 && ft_strcmp(n, "|") == 0))
		return (print_syntax_error("|"));
	else if (nnext && nnext->type != STR
		&& (ft_strcmp(c, "|") == 0 && ft_strncmp(n, "<", 1) == 0))
		return (print_syntax_error("|"));
	return (TRUE);
}

t_bool	check_valid2(t_token *pre, t_token *cur, t_token *nxt)
{
	char	*s;

	s = cur->data;
	if (!pre && !nxt)
	{
		if (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0
			|| ft_strcmp(s, "<") == 0 || ft_strcmp(s, "<<") == 0)
			return (print_syntax_error("newline"));
		else if (ft_strcmp(s, "|") == 0)
			return (print_syntax_error("|"));
	}
	else if (!nxt)
		return (check_valid4(cur));
	else if (!pre)
	{
		if (ft_strcmp(s, "|") == 0)
			return (print_syntax_error("|"));
	}
	else
		return (check_valid3(cur, nxt));
	return (TRUE);
}

t_bool	check_valid(t_token *pre, t_token *cur)
{
	t_token	*nxt;

	nxt = cur->next;
	while (nxt && nxt->type == SPACES)
		nxt = nxt->next;
	if (!check_valid2(pre, cur, nxt))
	{
		g_glob.exit_stat = 258;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	chk_cmd_is_valid(void)
{
	t_token	*cur;
	t_token	*pre;

	pre = NULL;
	cur = g_glob.tok;
	while (cur)
	{
		if (cur->type == ERROR)
			return (syntax_error(pre, cur));
		else
		{
			if (!check_valid(pre, cur))
				return (FALSE);
		}
		pre = cur;
		cur = cur->next;
		while (cur && cur->type == SPACES)
			cur = cur->next;
	}
	g_glob.exit_stat = 0;
	return (TRUE);
}
