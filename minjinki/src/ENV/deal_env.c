/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:09:03 by MJKim             #+#    #+#             */
/*   Updated: 2023/05/04 16:30:39 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_env(char *s, t_env **env)
{
	int		i;
	int		len;
	char	*key;
	char	*target;

	i = -1;
	while (s[++i])
	{
		target = ft_strchr("\" $.", s[i]);
		if (target)
			break;
	}
	if (!target)
		len = ft_strlen(s);
	else
		len = ft_strchr(s, target[0]) - s;
	key = ft_strndup(s, len + 1);
	if (!key)
		return (ERROR);
	printf("%s\n", key);
	*env = env_search_key(key);
	free(key);
	return (len);
}

t_bool	convert_env(t_token *cur)
{
	int		i;
	int		len;
	char	*tmp;
	t_env	*env;

	if (!cur)
		return (TRUE);
	if ((cur->type == STR || cur->type == DOUBLE || cur->type == TMP))
	{
		i = -1;
		while (cur->data[++i])
		{
			while (cur->data[i] && cur->data[i] != '$')
				i++; // $ 나올 때까지 뒤로
			if (!(cur->data[i]))
				break ;
			tmp = ft_strndup(cur->data, i++); // $ 앞까지의 문자열 저장
			if (!tmp)
				return (FALSE);
			// good
			len = get_env(cur->data + i, &env);
			if (len == ERROR)
				return (FALSE);
			if (env)
			{ // 변수 value값 tmp에 이어 붙이기, env free하면 큰일남!! 복제한 거 아님
				tmp = do_join(tmp, env->val); // 헤더에 넣어야 함, l_scmd.c에 있음
				if (!tmp)
					return (FALSE);
			}
			tmp = do_join(tmp, &(cur->data[i + len])); // 공백 뒤부터 붙이기 -> 이거 따옴표 있으면 없애고 해야함
			free(cur->data);
			cur->data = tmp;
			i += len - 1; // 조건문 ++i 때문에 공백 없이 바로 다음에 $ 다시 붙는 경우 $ 넘어감 그래서 -1
		}
	}
	return (TRUE);
}

t_bool	remove_quotes(t_token *token)
{
	int		len;
	char	*tmp;

	while (token)
	{
		if (token->type == DOUBLE || token->type == SINGLE)
		{
			len = ft_strlen(token->data);
			if (token->data[0] == token->type && token->data[len - 1] == token->type)	// 양 끝이 따옴표인 경우
			{	// 따옴표 뗀 문자열로 업데이트
				tmp = ft_strndup(token->data + 1, len - 2);
				if (!tmp)
					return (FALSE);
				free(token->data);
				token->data = tmp;
			}
		}
		token = token->next;
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
	{
		if (!convert_env(cur))
			return (FALSE);
		ft_lstprint(&(g_glob.tok));
		cur = cur->next;
	}
	// if (!remove_quotes(token))	// 가장 바깥에 있는 따옴표 제거 -> 만약 한쪽에만 있으면 제거 x
	// 	return (FALSE);
	// if (!join_n_split(token))	// 토큰 내부 문자열 스페이스 기준으로 나누기 && 토큰 양 옆 토큰과 공백으로 구분되지 않으면 합치기
	// 	return (FALSE);
	// remove_spaces(token);	// SPACES 노드 없애기: tmp에다 SPACES 저장하고 pre->next = tmp->next 후 free(tmp)
	return (TRUE);
}
