/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:02 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/05 16:02:04 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	ft_putstr_fd(ft_strrchr(pwd, '/') + 1, 1);
	free(pwd);
}

void Check_leak()
{
	system("leaks --list minishell");
}

void	minishell(void)
{
	setting_signal();
	init_rl_catch_signals();
	
	ft_bzero(&g_glob, sizeof(g_glob));
	while (TRUE)
	{
		g_glob.cmd = readline(" minishell_$ ");
		if (!(g_glob.cmd))
			break;
		if (!parse(g_glob.cmd))
		{
			free_all();
			continue ;
		}
		handler_builtins();
		free_cmd(g_glob.cmd);
	}
}

int	main(int ac, char **av, char **env)
{
	atexit(Check_leak);
	(void)av;
	if (ac != 1)
		exit_with_code("usage: ./minishell\n", 126);
	init_env(&env);
	minishell();
	free_all();
	return (SUCCESS);
}
