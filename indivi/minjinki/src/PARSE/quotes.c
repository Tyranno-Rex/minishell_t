/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:24:44 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/16 16:34:25 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*malloc_node(int len, char *start)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		ft_lstclear(&(g_glob.tok));
		return (print_error("Fail to allocate memory: g_glob.tok\n"));
	}
	new->data = ft_calloc(len + 1, sizeof(char));
	if (!(new->data))
	{
		free(new);
		ft_lstclear(&(g_glob.tok));
		return (print_error("Fail to allocate memory: g_glob.tok->data\n"));
	}
	ft_strlcpy(new->data, start, len + 1);
	printf("%s\n", new->data);	/*** remove ***/
	return (new);
}

t_bool	split_quote(int len, char *start, char *cmd)
{
	int end;	// save index of 2nd quote

	ft_lstadd_back(&(g_glob.tok), malloc_node(len, start));
	if (*cmd == '\'')
		end = single_quote();	// check til single quote appears
	else if (*cmd == '\"')
		end = double_quote();	// check till double quote appears
	return (end + 1);	// return next index of closed quote
}

void	deal_quotes(char *cmd)
{
	int		i;
	char	*start;

	i = -1;
	start = cmd;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			i = split_quote(i, start, cmd + i);
			start = cmd + i;
		}
	}
}
