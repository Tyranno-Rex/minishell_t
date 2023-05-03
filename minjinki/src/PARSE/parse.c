/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:56 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/02 17:05:20 by minjinki         ###   ########.fr       */
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
	if (ft_strlen(cmd) == 0 || is_space_only(cmd))
		return (TRUE);
	if (!deal_quotes(cmd, -1) || !deal_spaces())
		return (FALSE);
	if (!deal_pipe_n_redi())
		return (FALSE);
	if (!set_pipe_n_redi())
		return (FALSE);
	// convert_env(&(g_glob.tok));
	ft_lstprint(&(g_glob.tok));
	//if (!chk_cmd_is_valid()) // syntax error
	//	return (print_syntax_error()); // return TRUE
	// if (!init_tree())
	// 	return (FALSE);
	return (TRUE);
}
// should add error handling
