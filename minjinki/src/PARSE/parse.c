/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:56 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/30 13:29:08 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	is_space_only(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_is_space(cmd[i]))
			return (FALSE);
	}
	return (TRUE);
}

t_bool	parse(char *cmd)
{
	if (is_space_only(cmd))
		return (FALSE);
	if (!deal_quotes(cmd) || !deal_spaces())
		return (free_all());
	ft_lstprint(&(g_glob.tok));
	if (!deal_pipe_n_redi())
		return (free_all());
	if (!set_pipe_n_redi())
		return (FALSE);
	//chk_cmd_is_valid(); // syntax error
	ft_lstprint(&(g_glob.tok));
	// init_tree();
	return (TRUE);
}
// should add error handling
