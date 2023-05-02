/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:50:17 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/02 14:08:48 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*add_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (token->type == REDI)
	{
		cmd->redi = add_redi(token);
		if (!(cmd->redi))
			return (FALSE);
		while (token->type != CMD)
			token = token->next;
	}
	cmd->scmd = add_scmd(token);
	if (!(cmd->scmd))
		return (FAlSE);
	// CMD, OPT, ARGV 아닐 때까지 token 뒤로 옮기기
	cmd->reditree = add_reditree(token);
	if (!(cmd->reditree))
		return (FALSE);
	return (cmd);
}
