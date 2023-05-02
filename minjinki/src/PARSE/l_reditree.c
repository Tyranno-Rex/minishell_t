/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_reditree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:03:49 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/02 17:32:50 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// 이러면 없는 거랑 할당 실패한 거랑 같이 처리됨... 아놔...
// 고민 좀 더 해보기...............................
t_bool	add_reditree(t_token *token, t_scmd *scmd)
{
	t_reditree	*reditree;

	reditree = NULL;
	if (token && (token->type == LREDI || token->type == HEREDOC
		|| token->type == RREDI || token->type == RRREDI))
	// 리다이렉션 뒤에 ARGV 다시 나올 때 처리 해야함..
	{
		reditree = ft_calloc(1, sizeof(t_reditree));
		if (!reditree)
			return (NULL);
		reditree->redi = add_redi(token);
		if (!(reditree->redi))
			return (NULL);
		token = token->next->next; // redi는 리다이렉션이랑 파일 하나니까 2만큼 옮김
		reditree->reditree = add_redutree(token);
		if (!(reditree->reditree))
			return (NULL);
	}
	else if (token && token->type != PIPE)
	// scmd에서 연속된 ARGV는 처리했기 때문에 여기서 파이프가 안 나온다면 무조건 ARGV
	{
		if (!join_argv(token, scmd->ori, scmd->av))
			return (NULL);
	}
	return (reditree);
}
