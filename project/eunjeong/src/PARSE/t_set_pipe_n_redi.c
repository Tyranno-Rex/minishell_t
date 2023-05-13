/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_set_pipe_n_redi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:56:11 by MJKim             #+#    #+#             */
/*   Updated: 2023/05/13 10:21:14 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** check if type is pipe or redirection
*/
void	check_type(t_token *cur)
{
	int	len;

	len = ft_strlen(cur->data);
	if (len > 2 || (*(cur->data) == PIPE && len > 1))
		cur->type = ERROR;
	else if (*(cur->data) == LREDI)
	{
		if (len == 1)
			cur->type = LREDI;
		else if (len == 2)
			cur->type = HEREDOC;
	}
	else if (*(cur->data) == RREDI)
	{
		if (len == 1)
			cur->type = RREDI;
		else if (len == 2)
			cur->type = RRREDI;
	}
	else if (*(cur->data) == PIPE)
		if (len == 1)
			cur->type = PIPE;
}

t_bool	split_pipe_n_redi(t_token *cur, int type, char *redi)
{
	char	*data;
	t_token	*new;

	cur->type = PIPE;
	free(cur->data);
	cur->data = ft_strdup("|");
	if (!(cur->data))
		return (FALSE);
	data = ft_strdup(redi);
	if (!data)
		return (FALSE);
	new = ft_lstnew(type, data);
	if (!new)
		return (ft_free(data));
	ft_lstinsert(cur, new);
	return (TRUE);
}

t_bool	check_error(t_token *cur)
{
	if (ft_strcmp(cur->data, "|<") == 0)
	{
		if (!split_pipe_n_redi(cur, LREDI, "<"))
			return (FALSE);
	}
	else if (!ft_strcmp(cur->data, "|<<"))
	{
		if (!split_pipe_n_redi(cur, HEREDOC, "<<"))
			return (FALSE);
	}
	return (TRUE);
}

t_bool	set_pipe_n_redi(void)
{
	t_token	*cur;

	cur = g_glob.tok;
	while (cur)
	{
		if (cur->type == TMP)
			check_type(cur);
		else if (cur->type == ERROR)
			if (!check_error(cur))
				return (FALSE);
		cur = cur->next;
	}
	return (TRUE);
}
