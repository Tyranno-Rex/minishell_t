/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:24:44 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/11 15:20:34 by minjinki         ###   ########.fr       */
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
{	// 노드 할당
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
{	// 노드 할당 후 type과 data 지정, 할당한 노드 반환
	t_token	*new;

	new = malloc_node();
	if (!new)
		return (NULL);
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
{	// 따옴표 처리
	int		len;

	len = ft_strnlen(cmd + 1, type);	// 따옴표 바로 뒤 문자부터 길이 재기 시작, 다음 따옴표가 나올 때까지의 길이 
	if (*(cmd + len + 1) == '\0') // 닫히지 않은 따옴표는 STR으로 따옴표 포함해서 끝까지 저장
		ft_lstadd_back(&(g_glob.tok), add_node(STR, len + 1, cmd));
	else	// 닫힌 따옴표는 따옴표 저장 X: 왼쪽 따옴표 바로 다음 ~ 오른쪽 따옴표 바로 앞
		ft_lstadd_back(&(g_glob.tok), add_node(type, len, cmd + 1));
	if (*(cmd + len + 1) && *(cmd + len + 1) == ' ')
		// 위에서 저장한 문자열 바로 다음이 공백이면 공백 노드 추가
		ft_lstadd_back(&(g_glob.tok), add_node(SPACES, 1, " "));
	return (len + 1);
}

/*
** split_quote()
**	first step of tokenization
** 	split by quotes
*/
int	split_quote(int len, const char *cmd, char *quote)
{
	int		end;
	t_token	*new;

	end = 0;
	if (cmd != quote)	// 따옴표 아닌 경우
	{	// 일반 문자열로 저장
		new = add_node(STR, len, cmd);
		if (!new)
			return (ERROR);
		ft_lstadd_back(&(g_glob.tok), new);
	}
	if (quote && *quote == SINGLE)	// 홑따옴표
		end = quotes(SINGLE, quote);
	else if (quote && *quote == DOUBLE)	// 겹따옴표
		end = quotes(DOUBLE, quote);
	return (end + 1);	// 처리한 문자 바로 다음
}

t_bool	deal_quotes(char *cmd, int i)
{
	int			gap;
	int			last;
	const char	*start = cmd;	// 25줄 때문에.. start 내부 값을 바꾸지 않기 때문에 상관 없음

	last = 0;
	while (cmd[++i])
	{
		if (cmd[i] == SINGLE || cmd[i] == DOUBLE)
		{	// 따옴표인 경우: cmd + i를 전달하기 때문에 i에 last를 빼주어야 cmd + i부터의 길이를 전달할 수 있음
			gap = split_quote(i - last, start, cmd + i);
			if (gap == ERROR)
				return (FALSE);
			i += gap - 1;	// 처리한 만큼 i 뒤로 옮기기: gap이 와야 하나 while 조건문에 ++i 때문에 -1
			start = cmd + i + 1;	// 처리한 문자 바로 뒤 가리키기: i += gap - 1이라 + 1
			last = i + 1;	// 마지막으로 처리한 문자 바로 뒤의 인덱스
		}
	}
	if (start == cmd)	// 따옴표가 없는 경우 STR으로 전체 저장
		if (!ft_lstadd_back(&(g_glob.tok), add_node(STR, i, cmd)))
			return (print_error("Fail to tokenize\n"));
	// ft_lstprint(&g_glob.tok);
	// printf("start: %s\n", start);
	if (start != cmd && *start)		// 따옴표는 처리 다 했는데 따옴표 뒤에 문자가 있는 경우
		if (split_quote(i + 1, start, NULL) == ERROR)
			return (print_error("Fail to tokenize: quotes\n"));
	return (TRUE);
}
