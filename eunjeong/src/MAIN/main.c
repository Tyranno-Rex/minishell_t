/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:02 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/04 14:52:22 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


////////////////////////////////////////////////////////////////////////////////////////
///////////////////////머리아파서 파일 나누는거 포기 main에서만 작업한다///////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


int check_single_redirect()
{
	t_token *proc_data;
	char	**cmd_argv;
	int		origin_io[2];
	int		cmd_count;

	cmd_argv = make_tok2D();
	cmd_count = ft_matrixlen(cmd_argv);
	cmd_argv = make_tok2D();
	proc_data = g_glob.tok;
	// 해당 들어온 값이 1개이여야하고
	if (cmd_count == 1)
	{
		// builtin 값이 0이어야 한다.
		if (!is_builtin(cmd_argv[0]))
		{
			save_origin_io(origin_io);
			if (do_redirect(proc_data))
				g_glob.exit_stat = 1;
			restore_origin_io(origin_io);
			// 해당 부분 개별 요소 free를 안해줌
			free(cmd_argv);
			return (1);
		}
	}
	// 해당 부분 개별 요소 free를 안해줌
	free(cmd_argv);
	return (0);
}

void executor()
{
	if (check_single_builtin())
		return ;
	if (check_single_redirect())
		return ;
	// make_child();
	// wait_child();
}


////////////////////////////////////////////////////////////////////////////////////////
///////////////////////머리아파서 파일 나누는거 포기 main에서만 작업한다///////////////////////////
////////////////////////////////////////////////////////////////////////////////////////





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
	
	while (TRUE)
	{
		g_glob.cmd = readline(" minishell_$ ");
		if (!(g_glob.cmd))
			return ;
		if (!parse(g_glob.cmd))
		{
			free_cmd(g_glob.cmd);
			continue ;
		}
		env_2D();
		executor();
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
