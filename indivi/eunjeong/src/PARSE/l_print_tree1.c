/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_print_tree1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:31:16 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/02 14:48:04 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_redi(t_redi *redi)
{
	if (redi)
	{
		printf("redirection:\n");
		if (redi->type == LREDI || redi->type == RREDI)
			printf("%c ", redi->type)
		else
			printf("%c%c ", redi->type / 100, redi->type % 100);
		printf("%s\n-------------------------------\n", redi->av);
	}
}

void	print_reditree(t_reditree *reditree)
{
	if (reditree)
	{
		print_redi(reditree->redi);
		print_reditree(reditree->reditree);
	}
}

void	print_scmd(t_scmd *scmd)
{
	int	i;

	if (scmd)
	{
		printf("cmd:\n");
		printf("original: %s\n", scmd->ori);
		printf("simple: %s\n", scmd->scmd);
		printf("option: %s\n", scmd->opt);
		i = -1;
		while (scmd->av && scmd->av[++i])
			printf("av %d: %s\n", i, av[i]);
		printf("-------------------------------\n");
	}
}

void	print_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		print_redi(cmd->redi);
		print_scmd(cmd->scmd);
		print_reditree(cmd->reditree);
	}
}

void	print_tree()
{
	if (!(g_glob.tree))
		return ;
	printf("--------- print_tree ----------\n");
	print_cmd(&(g_glob.tree->cmd));
	print_pipe(&(g_glob.tree->pipe));
}
