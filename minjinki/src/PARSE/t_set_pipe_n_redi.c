/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_set_pipe_n_redi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:56:11 by MJKim             #+#    #+#             */
/*   Updated: 2023/05/05 12:03:48 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** check if type is pipe or redirection
*/
void	check_type(t_token *cur)
{	// 파이프, 리다이렉션 각각에 맞게 타입 지정
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

// 구문 에러 처리 -> 해야함
t_bool	deal_lredis(char *redi)
{
	(void)redi;
	// check_error if문 내에 있는 내용 여기로 빼기
	// length에 따라서 60할 지 6060할 지 조건으로 넣기
	return (TRUE);
}

t_bool	split_pipe_n_redi(t_token *cur, int type, char *redi)
{
	char	*data;
	t_token	*new;

	cur->type = PIPE;
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

/*
** check if type ERROR is |< or |<< -> should be splited as | < and | <<
*/
// |< |<<는 동작해야하므로 띄워 놓는다: 진행 중
t_bool	check_error(t_token *cur)
{
	char	*tmp;

	tmp = cur->data;
	if (!ft_strcmp(cur->data, "|<") && !ft_strchr("<|>", cur->data[2]))
	{
		if (!split_pipe_n_redi(cur, LREDI, "<"))
			return (FALSE);
	}
	else if (ft_strcmp(cur->data, "|<<") && !ft_strchr("<|>", cur->data[3]))
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
	{	// TMP면 타입 지정, ERROR인 경우 |<, |<<는 정상 노드로 처리
		if (cur->type == TMP)
			check_type(cur);
		else if (cur->type == ERROR)
			if (!check_error(cur))	// 진행 중
				return (FALSE);
		cur = cur->next;
	}
	return (TRUE);
}
// 파이프나 리다이 반복일 때 제대로 안 돌아가는 듯
// |<a 이런 경우 제대로 안돌아감
// |< 넣었을 때 메모리 이중 해제 발생.. -> 해결
// -> cur->data tmp에 넣고 메모리 해제해서 그런가