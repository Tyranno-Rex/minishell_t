/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:02 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/16 15:52:20 by minjinki         ###   ########.fr       */
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

int	minishell(void)
{
	char	*cmd;

	while (TRUE)
	{
		print_pwd();
		cmd = readline(" minishell_$ ");
		add_history(cmd);
		parse(cmd);
		free(cmd);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
		exit_with_code("usage: ./minishell\n", 126);
	copy_env(&env);
	minishell();
	free_all();
}
