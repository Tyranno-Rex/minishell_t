/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:02 by minjinki          #+#    #+#             */
/*   Updated: 2023/04/04 16:17:08 by minjinki         ###   ########.fr       */
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

void	minishell(void)
{
	while (TRUE)
	{
		print_pwd();
		g_glob.cmd = readline(" minishell_$ ");
		add_history(g_glob.cmd);
		if (!parse(g_glob.cmd))
		{
			free_all();
			continue ;
		}
		free_cmd(g_glob.cmd);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
		exit_with_code("usage: ./minishell\n", 126);
	init_env(&env);
	minishell();
	free_all();
	return (SUCCESS);
}
