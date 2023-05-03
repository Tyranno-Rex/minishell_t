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
	if ((cur->type == STR || cur->type == TMP))
	{
		i = -1;
		while (cur->data[++i])
		{
			while (cur->data[i] && cur->data[i] != '$')
				i++; // $ 나올 때까지 뒤로
			tmp = ft_strndup(cur->data, i); // $ 앞까지의 문자열 저장
			if (!tmp)
				reutrn (FALSE);
			len = ft_strchr(" $", cur->data[++i]) - &(cur->data[i]); // 환경변수 뒤에서 가장 먼저 나오는 공백이나 $까지의 길이, 없으면 \0까지의 길이
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

// test