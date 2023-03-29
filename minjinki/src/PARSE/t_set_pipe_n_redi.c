/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_set_pipe_n_redi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MJKim <zinnnn37@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:56:11 by MJKim             #+#    #+#             */
/*   Updated: 2023/03/29 14:56:11 by MJKim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** check if type is pipe or redirection
*/
t_bool	check_type(t_token *cur)
{

}

/*
** check if type ERROR is |< or |<< -> should be splited as | < and | <<
*/
t_bool	check_error(t_token *cur)
{

}

t_bool	set_pipe_n_redi(void)
{
	t_token	*cur;

	cur = g_glob.tok;
	while (cur)
	{
		if (cur->type == TMP)
			if (!check_type(cur))
				return (FALSE);
		else if (cur->type == ERROR)
			if (!check_error(cur))
				return (FALSE);
		cur = cur->next;
	}
	return (TRUE);
}
