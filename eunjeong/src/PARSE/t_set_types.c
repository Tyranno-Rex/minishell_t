/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_set_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:47:34 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/28 16:06:13 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_types(void)
{
	int		flag;
	t_token	*cur;
	t_token	*tmp;

	flag = CMD;
	tmp = NULL;
	cur = g_glob.tok;
	while (cur)
	{
		cur = cur->next;
	}
}
