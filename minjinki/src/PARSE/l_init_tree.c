/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_init_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:19:43 by MJKim             #+#    #+#             */
/*   Updated: 2023/05/02 14:09:21 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	init_tree(void)
{
	t_token	*token;

	g_glob.root = ft_calloc(1, sizeof(t_tree));
	if (!(g_glob.root))
		return (FALSE);
	token = g_glob.tok;
	g_glob.root->cmd = add_cmd(token);
	if (!(g_glob.root->cmd))
		return (FALSE);
	// 위에서 파이프 이전 cmd, redi는 다 처리 -> pipe부터 확인하면 됨
	while (token && token->type != PIPE)
		token = token->next;
	if (token)
	{
		g_glob.root->pipe = add_pipe(token);
		if (!(g_glob.root->pipe))
			return (FAlSE);
	}
}
