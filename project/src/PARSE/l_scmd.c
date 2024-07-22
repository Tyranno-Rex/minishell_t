/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_scmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:58:01 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/02 17:23:14 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



t_bool	join_argv(t_token *token, char *ori, char **av)
{
	int		i;
	int		cnt;
	t_token	*tmp;

	cnt = 0;
	tmp = token
	while (++cnt && tmp && tmp->data == ARGV)
		tmp = tmp->next;
	av = ft_calloc(cnt, sizeof(char *));
	i = -1;
	while (++i < cnt - 1)
	{
		ori = do_join(ori, token->data);
		av[i] = ft_strdup(token->data);
		if (!ori || !(av[i]))
			return (FALSE);
		token = token->next;
	}
	return (TRUE);
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
		scmd->ori = do_join(scmd->ori, token->data);
		if (!(scmd->opt) || !(scmd->ori))
			return (NULL);
		token = token->next;
		if (!join_argv(token, scmd->ori, scmd->av))
			return (NULL);
		//	-> 중복은 지우고 중복 아닌 건 join으로 합쳐서 -abc... 형태로
		// av에는 OPT 이하 ARGV들 저장
		// ori에 cmd 전체(e.g. echo -n a b c" d") -> strjoin
	}
	return (scmd);
}
