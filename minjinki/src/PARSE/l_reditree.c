/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_reditree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:03:49 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/02 16:15:07 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_reditree	*add_reditree(t_token *token)
{
	t_reditree	*reditree;

	reditree = NULL;
	if (token)
	{
		reditree = ft_calloc(1, sizeof(t_reditree));
		reditree->redi = add_redi(token);
		token = token->next->next; // redi는 리다이렉션이랑 파일 하나니까 2만큼 옮김
		reditree->reditree = add_redutree(token);
	}
	return (reditree);
}
