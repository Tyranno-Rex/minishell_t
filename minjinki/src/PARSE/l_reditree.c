/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_reditree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:03:49 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/02 14:06:00 by minjinki         ###   ########.fr       */
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
		// add_redi(token);
		// token 뒤로 옮기기
		// token 있고 type == REDI면 add_reditree 다시 호출
	}
	return (reditree);
}
