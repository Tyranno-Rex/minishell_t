/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:02:19 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/11 18:02:36 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	minishell(void)
{
	char			*cmd;

	while (TRUE)
	{
		cmd = readline("minishell_$> ");
		add_history(cmd);
		free(cmd);
	}
	return (SUCCESS);
}
