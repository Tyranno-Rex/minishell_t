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
///////////////////////머리아파서 파일 나누는거 포기 main에서만 작업한다////////////////////
////////////////////////////////////////////////////////////////////////////////////////

// define pipe end
# define READ_END	0
# define WRITE_END	1

// define pipe
# define NOW	0
# define PREV	1

int	is_last_cmd(t_token *proc_data)
{
	t_glob tmp;
	char	*data;

	tmp = g_glob;
	while (tmp.tok->next != NULL)
	{
		data = ft_strdup(tmp.tok->data);
		tmp.tok = tmp.tok->next;
	}	
	return (proc_data->data == data);
}

int	is_first_cmd(t_token *proc_data)
{
	return (proc_data->data == g_glob.tok->data);
}


int	ft_dup2(int fildes, int fildes2)
{
	int	ret;

	ret = dup2(fildes, fildes2);
	if (ret == -1)
	{
		perror("dup2 error occurred");
		exit(EXIT_FAILURE);
	}
	return (ret);
}


pid_t	ft_fork(void)
{
	pid_t	ret;

	ret = fork();
	if (ret == -1)
	{
		perror("fork error occurred");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

void	fl_redirect(t_token *proc, int pip[2][2], int *origin)
{
	if (is_first_cmd(proc))
		ft_dup2(origin[READ_END], pip[PREV][READ_END]);
	if (is_last_cmd(proc))
		ft_dup2(origin[WRITE_END], pip[NOW][WRITE_END]);
}



void 	execute_child(t_token *proc, int pip[2][2], int *ofd)
{
	char **cmd_argv;
	
	close(pip[NOW][READ_END]);
	fl_redirect(proc, pip, ofd);
	cmd_argv = make_tok2D();
	if (is_builtin(cmd_argv[0]))
		execute_builtin(cmd_argv[0]);
	else
		execute_execve(cmd_argv);
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

void	child_sig_handler(int signo)
{
	if (signo == SIGINT)
		ft_putendl_fd("", STDERR_FILENO);
	else if (signo == SIGQUIT)
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
	exit(128 + signo);
}

void	reset_signal(pid_t pid, int here_flag)
{
	if (pid == 0)
	{
		signal(SIGINT, child_sig_handler);
		if (here_flag)
			signal(SIGQUIT, SIG_IGN);
		else
			signal(SIGQUIT, child_sig_handler);
	}
	else
		signal(SIGINT, SIG_IGN);
}

void	make_child()
{
	t_token	*proc_node;
	int		origin_io[2];
	int		pipe[2][2];
	pid_t	pid;

	save_origin_io(origin_io);
	(ft_pipe(pipe[PREV]), close(pipe[PREV][WRITE_END]));
	proc_node = g_glob.tok;
	while (proc_node->next != NULL)
	{
		ft_pipe(pipe[NOW]);
		pid = ft_fork();
		reset_signal(pid, 0);
		if (pid == 0)
			return ;
			execute_child(proc_node, pipe, origin_io);
		// pid_list_add(&data->pid_list, pid);
		close(pipe[PREV][READ_END]);
		close(pipe[NOW][WRITE_END]);
		pipe[PREV][READ_END] = pipe[NOW][READ_END];
		proc_node = proc_node->next;
	}
	close(pipe[NOW][READ_END]);
	close(origin_io[READ_END]);
	close(origin_io[READ_END]);
}


// 시그널 처리 함수들

static int	_wstatus(int status)
{
	int	return_val;

	return_val = status & 0177;
	return (return_val);
}

int	wifsignaled(int status)
{
	int	return_val;

	return_val = ((_wstatus(status) != 0177) && (_wstatus(status) != 0));
	return (return_val);
}

int	wtermsig(int status)
{
	int	return_val;

	return_val = _wstatus(status);
	return (return_val);
}

int	wexitstatus(int status)
{
	int	return_val;

	return_val = ((unsigned)status >> 8) & 0xff;
	return (return_val);
}

// 이거 뭐를 넘겨줘야 할지 모르겠음
pid_t	ft_waitpid(pid_t pid, int *stat_loc, int options)
{
	pid_t	ret;

	ret = waitpid(pid, stat_loc, options);
	if (ret == -1)
	{
		perror("waitpid error occurred");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

void wait_child(t_data *data)
{
	t_token 	*tmp;
	int			status;
	int			status_tmp;

	status_tmp = 0;
	tmp = g_glob.tok;
	while (tmp->next != NULL)
	{
		// 이거 뭘 전달해야할까요?
		// ft_waitpid(&status, 0)
		status _tmp = status;
		if (wifsignaled(status))
			status = 128 + wtermsig(status);
		else
			status = wexitstatus(status);
		g_glob.exit_stat = status;
		tmp = tmp->next;
	}
	if (status_tmp == SIGINT || status_tmp == SIGQUIT)
	{
		if (status_tmp == SIGQUIT)
			ft_putendl_fd("QUIT: 3", STDOUT_FILENO);
		else
			ft_putendl_fd("", STDOUT_FILENO);
	}
}

void executor()
{
	if (check_single_builtin())
		return ;
	if (check_single_redirect())
		return ;
	// 여기 까지는 실행은 됨 하지만 메모리 릭 존재(메모리 릭 존재하는 이유 알고 있음) 표시 해뒀음

	// 불안한건 2개에요.
	make_child();
	wait_child();
}


////////////////////////////////////////////////////////////////////////////////////////
///////////////////////머리아파서 파일 나누는거 포기 main에서만 작업한다////////////////////
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
