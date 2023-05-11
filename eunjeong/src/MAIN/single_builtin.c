#include "../../include/minishell.h"

# define READ_END	0
# define WRITE_END	1

// char    **make_tok2D(void)
// {
//     t_glob  tmp;
//     int     cnt;
//     char    **av_argv;

//     tmp = g_glob;
//     cnt = 0;
//     while (tmp.tok)
//     {
//         tmp.tok = tmp.tok->next;
//         cnt++;
//     }
    
//     av_argv = calloc(cnt, sizeof(char *));
    
//     tmp.tok = g_glob.tok;
//     if (!tmp.tok)
//         return (NULL);
//     cnt = -1;
//     while (tmp.tok)
//     {
//         av_argv[++cnt] = ft_strdup(tmp.tok->data);
//         tmp.tok = tmp.tok->next;
//     }
//     return (av_argv);
// }

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
	else if (ft_strncmp(cmd, "env", 3) == 0 && num == 2)
		ft_exec_env();
	else if (ft_strncmp(cmd, "cd", 2) == 0 && num == 3)
		ft_exec_cd();
	else if (ft_strncmp(cmd, "export", 6) == 0 && num ==  4)
		ft_exec_export();
	else if (ft_strncmp(cmd, "unset", 5) == 0 && num ==  5)
		ft_exec_unset();
	else if (ft_strncmp(cmd, "echo", 4) == 0 && num == 6)
		ft_exec_echo();
	else if (ft_strncmp(cmd, "exit", 4) == 0 && num == 7)
		ft_exec_exit();
	return (0);
}

int	open_redirect(t_token *redir)
{
	int		fd;
	char	*err_msg;

	err_msg = ft_strjoin("minishell: ", redir->next->data);
	// 문제는 filename에 대한 확신이 없음
	// filename이 옆에 꺼라고 > 생각하니까 next의 data라고 정의함.
	if (!ft_strcmp(redir->data, ">") || !ft_strcmp(redir->data, ">>"))
	{
		// 출력 리다이렉션일 경우 (덮어 쓰기)
		if (!ft_strcmp(redir->data, ">>") )
			// fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			fd = open(redir->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// 출력 리다이렉션(새 파일 생성)일 경우
		else
			// fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			fd = open(redir->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(err_msg), free(err_msg), -1);
		(ft_dup2(fd, STDOUT_FILENO), close(fd));
	}
	else
	{
		// 입력 리다이렉션(파일에서 입력)일 경우
		fd = open(redir->next->data, O_RDONLY, 0644);
		if (fd == -1)
			return (perror(err_msg), free(err_msg), -1);
		// 입력 리다이렉션(Here Document)일 경우
		if (!ft_strcmp(redir->data, "<<"))
			// ft_unlink(redir->filename);
			// file name이 맞다면, 아래 함수는 동일함
			ft_unlink(redir->next->data);
		(ft_dup2(fd, STDIN_FILENO), close(fd));
	}
	free(err_msg);
	return (fd);
}

int	do_redirect(t_token *proc_data)
{
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

int	ft_matrixlenB(char **matrix)
{
	int	len;
	int count;
	
	len = 0;
	count = 0;
	while (matrix[len])
	{
		printf("command test: %s", matrix[len]);
		if (is_builtin(matrix[len]))
			count++;
		len++;
	}
	return (count);
}

int	check_single_builtin()
{
	t_token *proc_data;
	char	**cmd_argv;
	int		origin_io[2];
	int		builtin_num;


	builtin_num = 0;

	// bt_fp = NULL;
	// 해당 문제는 함수 포인터임 -> 함수 포인터 대신에 함수를 호출하는 방식으로 바꿈 

	// cmd_argv = cmd_list2arr(&proc_data->cmd_list);
	cmd_argv = make_tok2D();
	
	
	// 해당 문제는 전역 변수로 선언이 가능하기 때문에 아래로 대체
	proc_data = g_glob.tok; 
	// proc_data = list_peek_first_content(&data->proc_data_list);
	
	
	if (cmd_argv[0])
		// 실행해야하는 함수 찾기
		builtin_num = is_builtin_num(cmd_argv[0]);
	
	// 빌트인 함수의 갯수를 세는 것이 필요함
	// if (builtin_num && ft_matrixlenB(cmd_argv))
	if (builtin_num)
	{
		// 이건 똑같음
		save_origin_io(origin_io);
		
		// if (do_redirect(proc_data))
		// 	g_glob.exit_stat = 1;
		// else
		g_glob.exit_stat = handler_builtins_2(cmd_argv[0], builtin_num);
		restore_origin_io(origin_io);
		// 해당 부분 개별 요소 free를 안해줌
		free_matrix(cmd_argv);
		return (1);
	}
	// 해당 부분 개별 요소 free를 안해줌
	free_matrix(cmd_argv);
	return (0);
}