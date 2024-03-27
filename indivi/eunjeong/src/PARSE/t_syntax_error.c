/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_syntax_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:03:50 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/08 17:52:37 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	deal_error2(t_token *pre, char *s)
{
	if (!pre)
	{
		if (ft_strcmp(s, "|>") == 0 || ft_strcmp(s, "|>>") == 0)
			printf("minishell: syntax error near unexpected token '|'\n");
		else if (ft_strcmp(s, ">|") == 0 || ft_strcmp(s, "<<<") == 0)
			printf("minishell: syntax error near unexpected token 'newline'\n");
		else
			printf("minishell: syntax error: %s\n", s);
	}
	else if (pre)
	{
		if (ft_strcmp(s, ">|") == 0 || ft_strcmp(s, "|>") == 0
			|| ft_strcmp(s, "|>>") == 0 || ft_strcmp(s, "<<<") == 0)
			printf("minishell: syntax error near unexpected token 'newline'\n");
		else
			printf("minishell: syntax error: %s\n", s);
	}
}

void	deal_error(t_token *pre, t_token *cur)
{
	char	*s;

	s = cur->data;
	if (ft_strcmp(s, ">>|") == 0 || ft_strcmp(s, "<|") == 0
		|| ft_strcmp(s, "<<|") == 0 || ft_strcmp(s, "<<<|") == 0)
		printf("minishell: syntax error near unexpected token '|'\n");
	else if (ft_strcmp(s, ">>>") == 0)
		printf("minishell: syntax error near unexpected token '>'\n");
	else if (ft_strcmp(s, ">>>|") == 0)
		printf("syntax error near unexpected token '>|'\n");
	else if (ft_strncmp(s, ">>>>", 4) == 0)
		printf("minishell: syntax error near unexpected token '>>'\n");
	else if (ft_strncmp(s, "<<<<<", 5) == 0)
		printf("minishell: syntax error near unexpected token '<<'\n");
	else if (ft_strncmp(s, "<<<<", 4) == 0)
		printf("minishell: syntax error near unexpected token '<'\n");
	else if (ft_strncmp(s, "||", 2) == 0)
		printf("minishell: syntax error near unexpected toke '||'\n");
	else
		deal_error2(pre, s);
}

t_bool	syntax_error(t_token *pre, t_token *cur)
{
	deal_error(pre, cur);
	g_glob.exit_stat = ERR_UNEXPEC;
	return (FALSE);
}
