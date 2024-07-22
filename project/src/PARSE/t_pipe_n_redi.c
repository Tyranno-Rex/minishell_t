/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pipe_n_redi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:29 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/04 19:11:44 by minjinki         ###   ########.fr       */
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
	c = *s;	// 문자열 시작 저장
	new = ft_lstnew(ERROR, NULL);
	if (!new)
		return (FALSE);
	while (++i < len)
	{
		if (s[i] != c)	// 파이프 || 리다이렉션이 다른 게 나왔을 때 일단은 에러처리
		{
			new->data = ft_strndup(s, len);
			if (!(new->data))
				return (FALSE);
			ft_lstadd_back(tmp, new);	// type == ERROR인 노드 생성
			return (TRUE);
		}
	}
	new->type = TMP;	// 문자가 다 같으면 TMP인 노드 생성 후 붙이기
	new->data = ft_strndup(s, len);
	ft_lstadd_back(tmp, new);
	return (TRUE);
}

t_bool	split_by_pipe_n_redi(t_token **tmp, t_token *cur)
{	// pipe, redi 분리
	int		start;
	int		end;
	char	*pre;

	start = -1;
	pre = cur->data;	// 이전 문자열 시작 주소 저장(파이프, 리다이렉션 이전 문자열)
	while (cur->data[++start])
	{
		while (cur->data[start] && !ft_strchr("<|>", cur->data[start]))
			start++;	// 리다이렉션, 파이프 있는 위치까지 이동
		if (!(cur->data[start]))	// 없으면 문자열 전체 저장
			return (add_str(tmp, pre, ft_strlen(pre)));
		end = start;	// end pointer 초기화
		while (cur->data[++end])
		{	// 파이프, 리다이렉션이 더이상 안나오면 break: end는 파이프 || 리다이렉션 다음을 가리킴
			if (!ft_strchr("<|>", cur->data[end]))
				break ;
		}
		// 파이프, 리다이렉션 나오기 이전까지의 문자열 저장
		if (!add_str(tmp, pre, cur->data + start - pre))
			return (FALSE);
		// 파이프, 리다이렉션 저장
		if (!add_redi_pipe(tmp, cur->data + start, end - start))
			return (FALSE);
		start = end - 1;
		// start는 확인한 문자 바로 다음을 가리켜야 해서 end를 가리기면 되는데
		// while 조건문에서 ++start 하므로 -1을 해줘야 함
		pre = cur->data + end;	// 이하 동일
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
		{	// 일반 문자열 -> 파이프, 리다이렉션 구분
			if (!split_by_pipe_n_redi(&tmp, cur))
				return (print_error("Fail to allocate memory: deal_pipe_n_redi\n"));
		}
		else
		{	// 일반 문자열이 아닌 노드 -> 따옴표 노드: 구분 할 필요 없음
			if (!add_quotes(&tmp, cur))	// t_spaces.c에 있음
				return (print_error("deal_pipe_n_redi\n"));
		}
		cur = cur->next;
	}
	ft_lstclear(&(g_glob.tok));	// 기존 토큰 리스트 없애기
	g_glob.tok = tmp;	// 새로 만든 토큰 리스트로 업데이트
	return (TRUE);
}
