/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:56 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/28 18:50:20 by minjinki         ###   ########.fr       */
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

void	parse(char *cmd)
{
	if (is_space_only(cmd))
		return ;
	deal_quotes(cmd);
	deal_spaces();
	ft_lstprint(&(g_glob.tok));
	deal_pipe_n_redi();
	//chk_pipe_n_redi_is_valid();
	//chk_cmd_is_valid(); // syntax error
	ft_lstprint(&(g_glob.tok));
}
// should add error handling
