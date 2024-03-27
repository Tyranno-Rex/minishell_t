/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_redi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:01:19 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/02 16:04:14 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redi	*add_redi(t_token *token)
{
	t_redi	*redi;

	redi = NULL;
	if (token)
	{
		redi = ft_calloc(1, sizeof(t_redi));
		if (!redi)
			return (NULL);
		redi->type = token->type;
		redi->av = ft_strdup(token->next->data);
		if (!(redi->av))
			return (NULL);
	}
	return (redi);
}
