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

# define READ_END	0
# define WRITE_END	1

char    **make_tok2D(void)
{
    t_glob  tmp;
    int     cnt;
    char    **av_argv;

    tmp = g_glob;
    cnt = 0;
    while (tmp.tok)
    {
        tmp.tok = tmp.tok->next;
        cnt++;
    }
    
    av_argv = calloc(cnt, sizeof(char *));
    
    tmp.tok = g_glob.tok;
    if (!tmp.tok)
        return (NULL);
    cnt = -1;
    while (tmp.tok)
    {
        av_argv[++cnt] = ft_strdup(tmp.tok->data);
        tmp.tok = tmp.tok->next;
    }
    return (av_argv);
}

int	ft_dup(int fildes)
{
	int	ret;

	ret = dup(fildes);
	if (ret == -1)
	{
		perror("dup error occurred");
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

void	save_origin_io(int origin_io[2])
{
	origin_io[READ_END] = ft_dup(STDIN_FILENO);
	origin_io[WRITE_END] = ft_dup(STDOUT_FILENO);
}

void	restore_origin_io(int origin_io[2])
{
	ft_dup2(origin_io[READ_END], STDIN_FILENO);
	close(origin_io[READ_END]);
	ft_dup2(origin_io[WRITE_END], STDOUT_FILENO);
	close(origin_io[WRITE_END]);
}


int	is_builtin_num(char *cmd)
{
	int		count;
	t_glob	tmp;

	tmp = g_glob;
	
	if (!cmd)
		return (0);
	count = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "pwd", count) && count == 3)
		return (1);
	if (!ft_strncmp(cmd, "env", count) && count == 3)
		return (2);
	if (!ft_strncmp(cmd, "cd", count) && count == 2)
		return (3);
	if (!ft_strncmp(cmd, "export", count) && count == 6)
		return (4);
	if (!ft_strncmp(cmd, "unset", count) && count == 5)
		return (5);
	if (!ft_strncmp(cmd, "echo", count) && count == 4)
		return (6);
	if (!ft_strncmp(cmd, "exit", count) && count == 4)
		return (7);
	return (0);
}

int		handler_builtins_2(char *cmd, int num)
{
	if (ft_strncmp(cmd, "pwd", 3) == 0 && num == 1)
		ft_exec_pwd();
	else if (ft_strncmp(cmd, "exit", 4) == 0 && num == 2)
		ft_exec_exit();
	else if (ft_strncmp(cmd, "echo", 4) == 0 && num == 3)
		ft_exec_echo();
	else if (ft_strncmp(cmd, "env", 3) == 0 && num == 4)
		ft_exec_env();
	else if (ft_strncmp(cmd, "cd", 2) == 0 && num == 5)
		ft_exec_cd();
	else if (ft_strncmp(cmd, "export", 6) == 0 && num ==  6)
		ft_exec_export();
	else if (ft_strncmp(cmd, "unset", 5) == 0 && num ==  7)
		ft_exec_unset();
	return (0);
}

int	open_redirect(t_token *redir)
{
	int		fd;
	char	*err_msg;

	err_msg = ft_strjoin("minishell: ", redir->data);
	if (!ft_strcmp(redir->data, ">") || !ft_strcmp(redir->data, ">>"))
	{
		// 출력 리다이렉션(새 파일 생성)일 경우
		if (!ft_strcmp(redir->data, ">") )
			// fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			fd = open(redir->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// 출력 리다이렉션일 경우 (덮어 쓰기)
		else
			// fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			fd = open(redir->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror(err_msg), free(err_msg), -1);
		(ft_dup2(fd, STDOUT_FILENO), close(fd));
	}
	else
	{
		// 입력 리다이렉션(파일에서 입력)일 경우
		fd = open(redir->data, O_RDONLY, 0644);
		if (fd == -1)
			return (perror(err_msg), free(err_msg), -1);
		// 입력 리다이렉션(Here Document)일 경우
		if (!ft_strcmp(redir->data, "<<"))
			// ft_unlink(redir->filename);
			ft_unlink(redir->data);
		(ft_dup2(fd, STDIN_FILENO), close(fd));
	}
	free(err_msg);
	return (fd);
}

int	do_redirect(t_token *proc_data)
{
	// filepath와 리다이렉션 정보 들어가면 좋을 듯
	t_token	*node;

	node = proc_data;
	while (node->next != NULL)
	{
		if (open_redirect(node) < 0)
			return (1);
		node = node->next;
	}
	return (0);
}

int check_singel_builtin()
{
	t_token *proc_data;
	char	**cmd_argv;
	int		origin_io[2];
	int		builtin_num;

	proc_data = g_glob.tok;
	builtin_num = 0;
	cmd_argv = make_tok2D();
	if (cmd_argv[0])
		// 실행해야하는 함수 찾기
		builtin_num = is_builtin_num(cmd_argv[0]);
	if (list_size(cmd_argv) == 1 && builtin_num)
	{
		save_origin_io(origin_io);
		if (do_redirect(proc_data))
			g_glob.exit_stat = 1;
		else
			g_glob.exit_stat = handler_builtins_2(*cmd_argv, builtin_num);
		restore_origin_io(origin_io);
		free(cmd_argv);
		return (1);
	}
	free(cmd_argv);
	return (0);
}

void executor()
{
	if (check_single_builtin())
		return ;
	// if (check_single_redirect())
	// 	return ;
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
