/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:09:03 by MJKim             #+#    #+#             */
/*   Updated: 2023/05/11 17:37:15 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	deal_exit_stat(char **pre, char *next)
{
	char	*stat;

	stat = ft_itoa(g_glob.exit_stat);
	*pre = do_join(*pre, stat);
	*pre = do_join(*pre, next);
	free(stat);
}

/*
** 구분자 찾아서 그 까지의 부문자열 저장(key)
** key에 해당하는 환경변수 있다면 env에 해당 노드 저장, 없다면 NULL 저장
*/
int	get_env(char *s, t_env **env)
{
	int		i;
	int		len;
	char	*key;
	char	*target;

	i = -1;
	while (s[++i])
	{
		target = ft_strchr(" $.:\'\"", s[i]);	// 구분자 찾기
		if (target)	// 있으면 break
			break;
	}
	if (!target)	// 없으면 문자열 끝까지 전부 환경변수
		len = ft_strlen(s);
	else	// 있으면 target[0](구분자) 위치 찾아서 길이 구하기 (구분자의 주소값 - 문자열 시작 주소값)
		len = ft_strchr(s, target[0]) - s;
	key = ft_strndup(s, len);	// 구분자까지의 문자열 key에 저장
	if (!key)	// null guard
		return (ERROR);
	*env = env_search_key(key);	// key로 value 찾기
	free(key);	// ft_strdup()
	return (len);	// key의 길이
}

/*
** 환경변수 치환 함수
*/
t_bool	convert_env(t_token *cur)
{
	int		i;
	int		len;
	char	*tmp;
	//char	*stat;
	t_env	*env;

	if (!cur)
		return (TRUE);
	if ((cur->type == STR || cur->type == DOUBLE || cur->type == TMP))
	{	// 환경변수 치환해야 하는 노드 치환 
		i = -1;
		while (cur->data[++i])
		{
			while (cur->data[i] && cur->data[i] != '$')
				i++; // $ 나올 때까지 뒤로
			if (!(cur->data[i]))	// 없으면 break
				break ;
			tmp = ft_strndup(cur->data, i++); // $ 앞까지의 문자열 저장
			if (!tmp)
				return (FALSE);
			if (cur->data[i] == '?')
			{
				char	*stat;

				stat = ft_itoa(g_glob.exit_stat);
				tmp = do_join(tmp, stat);
				tmp = do_join(tmp, cur->data + i + 1);
				len = ft_strlen(stat);
				free(stat);
			}
			else
			{
				len = get_env(cur->data + i, &env);	// 환경변수 정보 && key 길이 얻기
				if (len == ERROR)	// null guard
					return (FALSE);
				if (env)
				{	// key가 있다면 대응되는 value tmp에 이어붙이기
					tmp = do_join(tmp, env->val);
					if (!tmp)
						return (FALSE);
				}
			}
			tmp = do_join(tmp, &(cur->data[i + len])); // 환경변수 뒤쪽 문자열 붙이기
			free(cur->data);	// 기존 data free
			cur->data = tmp;	// 환경변수 치환한 문자열
			i += len - 1; // 조건문 ++i 때문에 공백 없이 바로 다음에 $ 다시 붙는 경우 $ 넘어감 그래서 -1
		}
	}
	return (TRUE);
}

t_bool	join_n_split(t_token *token)
{
	int		i;		// index of matrixs
	char	*data;
	char	**matrix;
	t_token	*tmp;
	t_token	*new;	// update

	new = NULL;
	while (token)
	{
		matrix = ft_split(token->data, ' ');
		if (!matrix)
			return (FALSE);
		i = -1;
		while (matrix[++i])
		{
			data = ft_strdup(matrix[i]);
			if (!data)
				return (FALSE);
			tmp = ft_lstnew(STR, data);
			if (!tmp)
				return (FALSE);
			ft_lstadd_back(&(new), tmp);
			// matrix[i] 추가 후 SPACES 노드 하나 추가 만약 matrix[i+1]이 없으면 추가 안하기
			if (matrix[i+1])
			{
				tmp = ft_lstnew(SPACES, NULL);
				if (!tmp)
					return (FALSE);
				ft_lstadd_back(&(new), tmp);
			}
		}
		ft_lstclear(&(g_glob.tok));
		g_glob.tok = new;
		free_matrix(matrix);
		token = token->next;
	}

	return (TRUE);
}

void	remove_spaces(t_token *token)
{
	char	*tmp;
	t_token	*pre;
	t_token	*next;

	pre = NULL;
	while (token)
	{
		while (!pre && token->type == SPACES)	// 맨 앞에 나온 SPACES node 삭제
		{
			next = token;
			token = token->next;
			ft_lstdelone(next);
			token = token->next;
		}
		next = token->next;
		if (token->next && token->type != SPACES && token->next->type != SPACES)	// 노드가 공백으로 구분되지 않았을 때 두 data 합치고 노드 하나 삭제
		{	// 아 이거 STR이랑 TMP? 로 구분해야 할 듯
			tmp = ft_strjoin(token->data, next->data);
			free(token->data);
			token->data = tmp;
			token->next = next->next;
			ft_lstdelone(next);
		}
		else if (token->next && token->type != SPACES && token->next->type == SPACES)
		{
			next = token->next;
			token->next = next->next;
			ft_lstdelone(next);
			pre = token;
			token = token->next;
		}
	}
}

t_bool	deal_env(t_token **token)
{
	t_token	*cur;

	cur = *token;
	while (cur)
	{	// 환경변수 연결리스트 처음부터 확인하면서 치환
		if (!convert_env(cur))
			return (FALSE);
		cur = cur->next;
	}
	
	// if (!join_n_split(token))	// 토큰 내부 문자열 스페이스 기준으로 나누기 && 토큰 양 옆 토큰과 공백으로 구분되지 않으면 합치기
	// 	return (FALSE);
	// remove_spaces(token);	// SPACES 노드 없애기: tmp에다 SPACES 저장하고 pre->next = tmp->next 후 free(tmp)
	return (TRUE);
}
