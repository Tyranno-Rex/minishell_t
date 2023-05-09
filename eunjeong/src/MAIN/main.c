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




void 	execute_child(t_token *proc, int pip[2][2], int )
{

}

int	ft_pipe(int fildes[2])
{
	int	ret;

	ret = pipe(fildes);
	if (ret == -1)
	{
		perror("pipe error occurred");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

void	make_child()
{
	t_token	*proc_node;
	int		origin_io[2];
	int		pipe[2][2];
	pid_t	pid;

	save_origin_io(origin_io);
	(ft_pipe(pipe[0]), close(pipe[0][1]));
	proc_node = g_glob.tok;
	while (proc_node->next != NULL)
	{
		ft_pipe(pipe[1]);
		pid = ft_fork();
		reset_signal(pid, 0);
		if (pid == 0)
			execute_child(proc_node, pipe, origin_io);
		close(pipe[0][0]);
		close(pipe[1][1]);
		pipe[0][0] = pipe[1][0];
		proc_node = proc_node->next;
	}
	close(pipe[1][1]);
	close(origin_io[0]);
	close(origin_io[1]);
}

void executor()
{
	if (check_single_builtin())
		return ;
	if (check_single_redirect())
		return ;
	make_child();
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
