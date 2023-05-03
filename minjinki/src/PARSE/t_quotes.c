/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:24:44 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/01 16:38:27 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** parsing phase one
**	: split by quotes
** 
** e.g. ls -al "hi"'hello' "take me home" TT T
**	>> `ls -al `, `hi`,  `hello`,   ` `, `take me home`, ` TT T`-> data
**	>>	(STR), (DOUBLE), (SINGLE), (STR), (DOUBLE),      (STR)	-> type
** string between ` saved. ` is not saved
*/

t_token	*malloc_node(void)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		ft_lstclear(&(g_glob.tok));
		return (NULL);
	}
	return (new);
}

t_token	*add_node(int type, int len, const char *start)
{
	t_token	*new;

	new = malloc_node();
	new->type = type;
	new->data = ft_strndup(start, len);
	if (!(new->data))
		return (NULL);
	return (new);
}

/*
** ft_strnlen()
**	returns the length before a given char
**	returns ERROR(-1) if there is no char
*/
int	quotes(int type, char *cmd)
{
	int	len;

	len = ft_strnlen(cmd + 1, type);	// 따옴표 바로 뒤 문자부터 길이 재기 시작, 다음 따옴표가 나올 때까지의 길이 
	if (cmd + len != '\0')
		len += 1;	// 닫힌 따옴표인 경우
	ft_lstadd_back(&(g_glob.tok), add_node(type, len + 1, cmd));
	return (len);
}

/*
** split_quote()
**	first step of tokenization
** 	split by quotes
** 
** if (cmd != quote)
**	to execute quotes() immediatly
**	when openning quote appears very next to closing quote.
** 
** ERROR: to deal unclosed quote
** 
** end == index of closing quote
** I tried to return end + 1 but it doesn't work well🤔
*/
int	split_quote(int len, const char *cmd, char *quote)
{
	int		end;
	t_token	*new;

	end = 0;
	if (cmd != quote)
	{
		new = add_node(STR, len, cmd);
		if (!new)
			return (ERROR);
		ft_lstadd_back(&(g_glob.tok), new);
	}
	if (*quote == SINGLE)
		end = quotes(SINGLE, quote);
	else if (*quote == DOUBLE)
		end = quotes(DOUBLE, quote);
	return (end);
}

t_bool	deal_quotes(char *cmd, int i)
{
	int			gap;
	int			last;
	const char	*start = cmd;

	last = 0;
	while (cmd[++i])
	{
		if (cmd[i] == SINGLE || cmd[i] == DOUBLE)
		{
			gap = split_quote(i - last, start, cmd + i);
			if (gap == ERROR)
				return (FALSE);
			i += (gap + 1);
			start = cmd + i + 1;
			last = i + 1;
		}
	}
	if (start == cmd)
		if (!ft_lstadd_back(&(g_glob.tok), add_node(STR, i, cmd)))
			return (print_error("Fail to tokenize\n"));
	if (*start)
		if (split_quote(i + 1, start, cmd) == ERROR)
			return (print_error("Fail to tokenize: quotes\n"));
	return (TRUE);
}
