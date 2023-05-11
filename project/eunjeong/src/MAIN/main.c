/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:02 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/11 16:43:35 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
# define READ_END	0
# define WRITE_END	1


// int	ft_dup(int fildes)
// {
// 	int	ret;

// 	ret = dup(fildes);
// 	if (ret == -1)
// 	{
// 		perror("dup error occurred");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (ret);
// }


// void	save_origin_io(int origin_io[2])
// {
// 	origin_io[READ_END] = ft_dup(STDIN_FILENO);
// 	origin_io[WRITE_END] = ft_dup(STDOUT_FILENO);
// }

// // c0 p0 c1 p1 c2 p2 ... ck pk ck+1 pk+1 ... pn cn+1
// // p0 : 0, 1
// // p1 : 2, 3
// // pk : 2k, 2k + 1

int	ft_unlink(const char *path)
{
	int	ret;

	ret = unlink(path);
	if (ret == -1)
	{
		perror("unlink error occurred");
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

int	get_heredoc_input(char *filename, char *limiter)
{
	int		fd;
	int		wstatus;
	pid_t	pid;
	char	*input_line;

	fd = open(filename, O_WRONLY);
	pid = fork();
	reset_signal(pid, 1);
	if (pid == 0)
	{
		while (1)
		{
			input_line = readline("> ");
			if (ft_strcmp(input_line, limiter) == 0)
			{
				free(input_line);
				break ;
			}
			(ft_putendl_fd(input_line, fd), free(input_line));
		}
		exit(EXIT_SUCCESS);
	}
	(waitpid(pid, &wstatus, 0), close(fd));
	return (wexitstatus(wstatus));
}

int open_fd(t_token *block_token)
{
	int		fd = 0;
	char	*err_msg;
	t_token *block;

	
	block = block_token;
	err_msg = ft_strjoin("minishell: ", block->next->data);
	// 문제는 filename에 대한 확신이 없음
	// filename이 옆에 꺼라고 > 생각하니까 next의 data라고 정의함.
	if (!ft_strcmp(block->data, "<") || !ft_strcmp(block->data, "<<"))
	{
		// 입력 리다이렉션(파일에서 입력)일 경우
		fd = open(block->next->data, O_RDONLY, 0644);
		if (fd == -1)
			return (perror(err_msg), free(err_msg), -1);
		// 입력 리다이렉션(Here Document)일 경우
		if (!ft_strcmp(block->data, "<<"))
		{
			// filepath이것만 check하기
			get_heredoc_input(block->data, block->next->data);
			unlink(block->next->data);
		}
		(ft_dup2(fd, STDIN_FILENO), close(fd));
	}
	// 다음 파일



	else if (!ft_strcmp(block->data, ">") || !ft_strcmp(block->data, ">>"))
	{
		// 출력 리다이렉션일 경우 (덮어 쓰기)
		if (!ft_strcmp(block->data, ">>") )
			fd = open(block->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// 출력 리다이렉션(새 파일 생성)일 경우
		else if (!ft_strcmp(block->data, ">") || ft_strlen(block->data) == 1)
			fd = open(block->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (!ft_strcmp(block->data, "|") || ft_strlen(block->data) == 1)
			fd = open(block->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(err_msg), free(err_msg), -1);
		(ft_dup2(fd, STDOUT_FILENO), close(fd));
	}
	// 최종 파일에 적을 지 확인
	// if ()

	free(err_msg);
	return (fd);
}

void close_pipe_app(int *pip, int i, int pipe_num)
{
	int	j;
	int	save[2];

	save[0] = -1;
	save[1] = -1;
	j = 0;
	if (i)
		save[0] = i - 1;
	if (i != pipe_num + 1)
		save[1] = i;
	while (j < pipe_num)
	{
		if (j != save[0] && j != save[1])
		{
			close(pip[j * 2]);
			close(pip[j * 2 + 1]); 
		}
		j++;
	}
}


void executor()
{
	int			pipe_num;
	char 		**cmd;
	t_token 	*flow = g_glob.tok;
	t_token		*block_token;
	int			*pip;
	int			i = 0;
	int 		status;
	pid_t		pid;
	int			fd;

	pipe_num = pipe_len();
	cmd = (char **)malloc(sizeof(char *) * pipe_num + 1);
	pip = ft_calloc(4, pipe_num);
	while (pipe_num)
	{
		// 이거 문제 있음
		pipe(pip + (pipe_num - 1) * 2);
		// pipe(pip);
		pipe_num--;
	}

	pipe_num = pipe_len() + 1;

	// 여기 while문
	block_token = t_cmd_pipe(&flow);
	if (is_builtin(block_token->data) && (ft_strcmp(block_token->data, "exit") 
		|| ft_strcmp(block_token->data, "export") || ft_strcmp(block_token->data, "unset")
		|| ft_strcmp(block_token->data, "cd")))
		handler_builtins(block_token->data, block_token);
	
	pid = ft_fork();
	if (!pid)
	{
		//            파이프, 순서, 총 크기
		close_pipe_app(pip, i, pipe_num);
		
		// open_fd(); << fd , pipe 0, 1 << dup2();
		fd = open_fd(block_token);
		
		// exe();
		// close_pipe();
		// close_fd();
		exit(0);
	
	}
	waitpid(pid, &status, 0);
	// 여기까지 while문


	while (pipe_num--)
	{	

	}
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////추가되는 작업 main/////////////////////////////
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
