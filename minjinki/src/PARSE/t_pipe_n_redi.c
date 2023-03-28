/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe_n_redi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:29 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/28 18:58:04 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	add_str(t_token **tmp, char *s, int len)
{
	t_token	*new;

	new = ft_lstnew(STR, ft_strndup(s, len));
	if (!new)
		return (FALSE);
	ft_lstadd_back(tmp, new);
	return (TRUE);
}

t_bool	add_redi_pipe(t_token **tmp, char *s, int len)
{
	int		i;
	char	c;
	t_token	*new;

	i = 0;
	c = s[0];
	new = ft_lstnew(ERROR, NULL);
	if (!new)
		return (FALSE);
	while (i++ < len)
	{
		if (c != s[i])
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

	start = -1;
	while (cur->data[++start])
	{
		while (cur->data[start] && !ft_strchr("<|>", cur->data[start]))
			start++;
		if (!(cur->data[start]))
			return (add_str(tmp, cur->data, ft_strlen(cur->data)));
		end = start;
		printf("s[start]: %s\n", cur->data + start);
		while (cur->data[end++])
		{
			if (!ft_strchr("<|>", cur->data[end]))
				break ;
		}
		printf("s[end]: %s\n", cur->data + end);
		if (!add_str(tmp, cur->data, start))
			return (FALSE);
		if (!add_redi_pipe(tmp, cur->data + start, end - start))
			return (FALSE);
		start = end;
	}
	return (TRUE);
}
// start는 첫 <|>, end는 <|> 바로 뒤를 가리킴
// start랑 end 기준으로 함 나누고 뒤에 것도 반복문 내에서 분리
// start랑 end 인덱스는 맞게 나옴
// len을 추가해서 start랑 안 꼬이게 하기

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
				return (print_error("Fail to allocate memory: deal_pipe_n_redi\n"));
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
