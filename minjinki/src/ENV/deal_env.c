/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MJKim <zinnnn37@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:09:03 by MJKim             #+#    #+#             */
/*   Updated: 2023/03/29 16:09:03 by MJKim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	convert_env(t_token *cur)
{
	int		i;
	int		len;
	char	*tmp;
	char	*key;
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
			tmp = ft_strndup(cur->data, i); // $ 앞까지의 문자열 저장
			if (!tmp)
				reutrn (FALSE);
			len = ft_strchr(" $.", cur->data[++i]) - &(cur->data[i]); // 환경변수 뒤에서 가장 먼저 나오는 sep 까지의 길이, 없으면 \0까지의 길이
			key = ft_strdup(cur->data + i, len); // 공백이나 다음 $ 이전까지의 문자열 저장
			if (!key)
				return (FALSE);
			env = env_search_key(key);
			if (env)
			{ // 변수 value값 tmp에 이어 붙이기, env free하면 큰일남!! 복제한 거 아님
				tmp = do_join(tmp, env->val); // 헤더에 넣어야 함, l_scmd.c에 있음
				if (!tmp)
					return (FALSE);
			}
			tmp = do_join(tmp, cur->data[i + len], ft_strlen(&(cur->data[i + len]))); // 공백 뒤부터 붙이기
			free(cur->data);
			cur->data = tmp;
			free(key);
			i += len - 1; // 조건문 ++i 때문에 공백 없이 바로 다음에 $ 다시 붙는 경우 $ 넘어감 그래서 -1
		}
	}
	return (convert_env(cur->next));
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
				free(token->data);
				token->data = tmp;
			}
		}
		token = token->next;
	}
}

t_bool	deal_env(t_token *token)
{
	if (!convert_env(token))
		return (FALSE);
	if (!remove_quotes(token))	// 가장 바깥에 있는 따옴표 제거 -> 만약 한쪽에만 있으면 제거 x
		return (FALSE);
	if (!join_n_split(token))	// 토큰 내부 문자열 스페이스 기준으로 나누기 && 토큰 양 옆 토큰과 공백으로 구분되지 않으면 합치기
		return (FALSE);
}
