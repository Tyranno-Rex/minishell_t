/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_check_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:04:38 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/05 12:44:28 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	chk_cmd_is_valid(void)
{
	t_token	*cur;

	cur = g_glob.tok;
	while (cur)
	{
		if (cur->type == ERROR)
			return (syntax_error(cur));
		cur = cur->next;
	}
	return (TRUE);
}
