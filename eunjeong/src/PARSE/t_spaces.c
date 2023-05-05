/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_spaces.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:49:31 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/04 19:33:46 by minjinki         ###   ########.fr       */
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
{	// 공백 노드 추가
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
	int		n;
	char	*s;

	start = -1;
	n = ft_strlen(cur->data);
	while (cur->data[++start] && start < n)
	{	// 공백 나올 때까지 start 옮기기
		while (cur->data[start] && ft_is_space(cur->data[start]))
			start++;
		if (start > 0 && ft_is_space(cur->data[start - 1]))
			add_space(tmp);	// 공백이 있다면 공백노드 추가
		if (!(cur->data[start]))
			break ;
		len = ft_strnlen(&(cur->data[start]), ' ');	// 다음 공백까지의 길이
		s = ft_strndup(&(cur->data[start]), len);	// 다음 공백까지의 문자열 저장
		if (!s)
			return (free_lst(tmp));
		if (!ft_lstadd_back(tmp, ft_lstnew(STR, s)))// 만든 노드 붙이기
			return (free_lst(tmp));
		start += len;	// start를 확인한 다음 인덱스로 옮기기
	}
	// 마지막에 공백 나온 것도 넣어주기
	if (ft_lstlast(*tmp)->type != SPACES && ft_is_space(cur->data[start - 1]))
		add_space(tmp);
	return (TRUE);
}

t_bool	add_quotes(t_token **tmp, t_token *cur)
{	// cur에 저장된 정보 그대로 tmp 리스트에 붙이기
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

// 공백 기준으로 분리
t_bool	deal_spaces(void)
{
	t_token	*cur;
	t_token	*tmp;

	tmp = NULL;
	cur = g_glob.tok;
	while (cur)
	{
		if (cur->type == STR) // 일반 문자열은 공백 기준으로 분리
		{
			if (!split_by_space(&tmp, cur))
				return (print_error("Fail to allocate memory: split_by_spaces()\n"));
		}
		else	// 따옴표면 별 다른 처리 없이 전부 붙이기
		{
			if (!add_quotes(&tmp, cur))
				return (print_error("Fail to allocate memory: split_by_spaces()\n"));
		}
		cur = cur->next;
	}
	ft_lstclear(&(g_glob.tok));	// 기존 tok 지우고
	g_glob.tok = tmp;			// 지금 만든 리스트로 업데이트
	return (TRUE);
}
