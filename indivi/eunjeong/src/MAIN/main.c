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

// c0 p0 c1 p1 c2 p2 ... ck pk ck+1 pk+1 ... pn cn+1
// p0 : 0, 1
// p1 : 2, 3
// pk : 2k, 2k + 1

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
	
	fd = open(filename, O_WRONLY | O_CREAT);
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
	waitpid(pid, &wstatus, 0);
	close(fd);
	return (wexitstatus(wstatus));
}

char *get_next_path(t_token *block)
{
	t_token *tmp;
	char 	*str;

	tmp = block;
	while (tmp)
	{
		if (tmp->type != SPACES)
			break;
		tmp = tmp->next;
	}
	str = ft_strdup(tmp->data);
	return (str);
}

void	open_fd(t_token *block_token)
{
	t_token *block;
	char	*path;

	block = block_token;

	g_glob.oldfd[0] = dup(STDIN_FILENO);
	g_glob.oldfd[1] = dup(STDOUT_FILENO);

	if (!ft_strcmp(block->data, "<") || !ft_strcmp(block->data, "<<"))
	{
		path = get_next_path(block->next);
		if (path == NULL)
		{
			g_glob.fd[WEND] = -1;
			return ;
		}	
		g_glob.fd[WEND] = open(path, O_RDONLY, 0644);
		if (g_glob.fd[WEND] == -1)
			return ;
		if (!ft_strcmp(block->data, "<<"))
		{
			get_heredoc_input(block->next->data, block->next->data);
			unlink(block->next->data);
		}
		ft_dup2(g_glob.fd[WEND], STDIN_FILENO);
	}	
	else if (!ft_strcmp(block->data, ">") || !ft_strcmp(block->data, ">>"))
	{
		// close(g_glob.fd[REND]);
		path = get_next_path(block->next);
		if (path == NULL)
		{
			g_glob.fd[WEND] = -1;
			return ;
		}
		if (!ft_strcmp(block->data, ">>"))
			g_glob.fd[WEND] = open(block->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (!ft_strcmp(block->data, ">") || ft_strlen(block->data) == 1)
			g_glob.fd[WEND] = open(block->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_dup2(g_glob.fd[WEND], STDOUT_FILENO);
		close(g_glob.fd[WEND]);
	}
}


void close_pipe(int *pip, int pipe_num)
{
	close(pip[pipe_num]);
	close(pip[pipe_num + 1]);
}

// 파이프 단위로 나누어서 리다이렉션 단위로 나누기
void ft_exe(t_token *block)
{
	(void)block;
	t_token *in_pipe;

	if (check_single_excute())
		return ;
	
	in_pipe = get_till_redi_1(&block);
	while (in_pipe)
	{
		ft_execve(in_pipe);
		
		close(g_glob.fd[WEND]);
		close(g_glob.fd[REND]);
		dup2(g_glob.oldfd[0], STDIN_FILENO);
		close(g_glob.oldfd[0]);
		dup2(g_glob.oldfd[1], STDOUT_FILENO);
		close(g_glob.oldfd[1]);

		in_pipe = get_till_redi_1(&block);
	}
	
	
	// close(g_glob.fd[REND]);
	
	// printf("test 1: %d\n", g_glob.fd[WEND]);

	// while (in_pipe)
	// {
		// in_pipe_test = in_pipe;
		// while (in_pipe_test)
		// {
		// 	printf("%s", in_pipe_test->data);
		// 	in_pipe_test = in_pipe_test->next;
		// }
		
		// printf("%s\n", in_pipe->data);

		// if (is_builtin(in_pipe->data))
		// 	handler_builtins(in_pipe->data, in_pipe);
		// else	
		// 	ft_execve(in_pipe);
		// close(g_glob.fd[WEND]);
		// in_pipe = in_pipe->next;
		// in_pipe = get_till_redi_1(&block, &fd);
	// }
}

void executor()
{
	t_token 	*flow = g_glob.tok;
	t_token		*block_token;
	// t_token		*block_redi;
	// t_token		*redir_token;
	int			pipe_num;
	int			*pip;
	// int			i = 0;
	// int			fd;
	// pid_t		pid;

	pipe_num = pipe_len();
	pip = ft_calloc(4, pipe_num);
	while (pipe_num)
	{
		pipe(pip + (pipe_num - 1) * 2);
		pipe_num--;
	}
	pipe_num = pipe_len() + 1;
	
	block_token = t_cmd_pipe(&flow);
	ft_exe(block_token);

	// block_token = t_cmd_pipe(&flow);
	// while (block_token)
	// {
	// 	ft_exe(block_token);
	// }




	
	// while (block_token)
	// {
	// 	printf("%s\n", block_token->data);
	// 	block_token = t_cmd_pipe(&flow);
	// }
	// if (is_builtin(block_token->data) && (ft_strcmp(block_token->data, "exit") 
	// 	|| ft_strcmp(block_token->data, "export") || ft_strcmp(block_token->data, "unset")
	// 	|| ft_strcmp(block_token->data, "cd")))
	// 	handler_builtins(block_token->data, block_token);


	// block_redi = get_till_redi_1(block_token);
	
	// block_redi = get_till_redi_1(&flow);
	// while (block_redi)
	// {
	// 	printf("%s\n", block_redi->data);
	// 	block_redi = get_till_redi_1(&flow);
	// }
	

	// close_pipe_app(pip, i, pipe_num);
	// fd = open_fd(block_token);

	// redir_token = get_till_redi(&block_token);
	// while (block_token)
	// {
	// 	printf("redir : %s\n", block_token->data);
	// 	block_token = block_token->next;
	// }

	

	// ft_exe(block_token, fd);
	// ft_close_fd(block_token);


	// if (fd < 0)
	// 	g_glob.exit_stat = 1;
	// printf("%d\n", fd);
	// exit(EXIT_SUCCESS);

	// close_pipe(pip, pipe_num);
	// close_fd();


	// pid = ft_fork();
	// if (!pid)
	// {
	// 	//            파이프, 순서, 총 크기
	//	// close_pipe_app(pip, i, pipe_num);
	// 	// open_fd(); << fd , pipe 0, 1 << dup2();
	//	// ft_exe(block_token);
	// 	// close_pipe();
	// 	// close_fd();
	// 	exit(0);
		
	
	// }
	// waitpid(pid, &status, 0);
	// 여기까지 while문

	// while (pipe_num--)
	// {

	// }


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
		int i = 0;
		printf("redi check %d\n", i+= 1);
		g_glob.cmd = readline(" minishell_$ ");
		if (!(g_glob.cmd))
			return ;
		printf("redi check %d\n", i+= 1);
		if (!parse(g_glob.cmd))
		{
			free_cmd(g_glob.cmd);
			continue ;
		}
		printf("redi check %d\n", i+= 1);
		env_2D();
		printf("redi check %d\n", i+= 1);
		executor();
		printf("redi check %d\n", i+= 1);
		free_cmd(g_glob.cmd);
		printf("redi check %d\n", i+= 1);
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
