/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_scmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:58:01 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/02 17:15:29 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_ori(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	free(s1);
	s1 = NULL;
	return (res);
}

t_scmd	add_scmd(t_token *token)
{
	t_scmd	*scmd;
	t_token	*start;

	scmd = NULL;
	start = token;
	if (token)
	{
		scmd = ft_calloc(1, sizeof(t_scmd));
		scmd->scmd = ft_strdup(token->data);	// simple cmd
		scmd->ori = ft_strdup(token->data);
		if (!(scmd->scmd) || !(scmd->ori))
			return (NULL);
		token = token->next;
		scmd->opt = ft_strdup(token->data);		// options
		scmd->ori = join_ori(scmd->ori, token->data);
		if (!(scmd->opt) || !(scmd->ori))
			return (NULL);
		//	-> 중복은 지우고 중복 아닌 건 join으로 합쳐서 -abc... 형태로
		// av에는 OPT 이하 ARGV들 저장
		// ori에 cmd 전체(e.g. echo -n a b c" d") -> strjoin
	}
	return (scmd);
}
