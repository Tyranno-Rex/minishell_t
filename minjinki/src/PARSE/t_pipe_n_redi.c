/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe_n_redi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:29 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/25 19:05:40 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	split_by_pipe_n_redi(t_token **tmp, t_token *cur)
{
	int		start;
	int		end;
	char	*s;
	t_token	*new;

	start = -1;
	while (cur->data[++start])
	{
		while (cur->data[start] && !ft_strchr("<|>", cur->data[start]))
			start++;
		if (!(cur->data[start]))
			return (add_str(cur->data));
		end = start;
		while (cur->data[++end])
		{
			if (!ft_strchr("<|>", cur->data[end]))
				break ;
			// start는 첫 <|>, end는 <|> 바로 뒤를 가리킴
			// start랑 end 기준으로 함 나누고 뒤에 것도 반복문 내에서 분리
		}
	}
}

void	deal_pipe_n_redi(void)
{
	t_token	*cur;
	t_token	*tmp;

	tmp = NULL;
	cur = g_glob.tok;
	while (cur)
	{
		if (cur->type == STR)
		{
			split_by_pipe_n_redi(&tmp, cur);
		}
		else
		{
			if (!add_quotes(&tmp, cur))
				return ;
		}
		cur = cur->next;
	}
	ft_lstclear(&(g_glob.tok));
	g_glob.tok = tmp;
}
