////////////////////////////////////////////////////////////////////////////////////////
///////////////////////머리아파서 파일 나누는거 포기 main에서만 작업한다////////////////////
////////////////////////////////////////////////////////////////////////////////////////

// define pipe end
# define READ_END	0
# define WRITE_END	1

// define pipe
# define NOW	0
# define PREV	1


// 해당 내용 수정함
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


// 해당 내용 수정함
int	is_first_cmd(t_token *proc_data)
{
	return (proc_data->data == g_glob.tok->data);
}


// int	ft_dup2(int fildes, int fildes2)
// {
// 	int	ret;

// 	ret = dup2(fildes, fildes2);
// 	if (ret == -1)
// 	{
// 		perror("dup2 error occurred");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (ret);
// }


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

void	pip_redirect(t_token *proc_data, int write_end, int read_end)
{
	ft_dup2(read_end, STDIN_FILENO);
	close(read_end);
	ft_dup2(write_end, STDOUT_FILENO);
	close(write_end);
	// 리다이렉션 다시 진행해서 파일 열게됨
	if (do_redirect(proc_data))
		exit (EXIT_FAILURE);
}


void	execute_execve(char **cmd_argv)
{
	(void)cmd_argv;
	// 기존 함수

	// struct stat	sb;
	// char		*cmd_path;

	// if (cmd_argv[0][0] == 0)
	// 	(error_msg(cmd_argv[0], EN_CNOT_FIND), exit(EX_CNOT_FIND));
	// cmd_path = get_cmd_path(data, cmd_argv);
	// if (cmd_path == NULL)
	// 	(error_msg(cmd_argv[0], EN_CNOT_FIND), exit(EX_CNOT_FIND));
	// ft_stat(cmd_path, &sb);
	// if ((sb.st_mode & S_IFMT) == S_IFDIR)
	// 	(error_msg(cmd_argv[0], EN_IS_DIR), exit(EX_CNOT_EXEC));
	// else if (access(cmd_path, X_OK) == -1)
	// 	(error_msg(cmd_argv[0], EN_PER_DENIED), exit(EX_CNOT_EXEC));
	// ft_execve(cmd_path, cmd_argv, cmd_envp);
	
	
	ft_execve();
}


void 	execute_child(t_token *proc, int pip[2][2], int *ofd)
{
	char **cmd_argv;
	
	close(pip[NOW][READ_END]);
	// 첫번째 명령어인지 마지막 명령어인지 확인하고 pipe를 여는 작업을 진행함.
	fl_redirect(proc, pip, ofd);
	// dup 작업 및 리다이렉션 진행함.
	pip_redirect(proc, pip[NOW][WRITE_END], pip[PREV][READ_END]);
	cmd_argv = make_tok2D();
	if (is_builtin(cmd_argv[0]))
		handler_builtins(cmd_argv[0]);
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
			// 해당 부분 에러 존재함
			execute_child(proc_node, pipe, origin_io);
		// pid를 저장하는 함수를 만들어어 아마 waitpid에서 활용하는 것 같음
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

void wait_child(void)
{
	t_token 	*tmp;
	int			status;
	int			status_tmp;

	status_tmp = 0;
	tmp = g_glob.tok;
	while (tmp->next != NULL)
	{
		// 이거 뭘 전달해야할까요? 원본 코드
		// ft_waitpid(*((pid_t *)node->content), &status, 0);
		// ft_waitpid(&status, 0)
		status_tmp = status;
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



// char  **make_cmd_pipe(int pipe_num)
// {
// 	int 	i = pipe_num;
// 	int 	cnt = -1;
// 	char 	*tmp;
// 	char	**ret;
// 	char	**ret_2;
	
// 	ret = (char **)malloc(sizeof(char *) * pipe_num);
// 	ret_2 = (char **)malloc(sizeof(char *) * 2);
// 	tmp = g_glob.cmd;

// 	while (++cnt < i)
// 	{
// 		ret_2 = ft_split(tmp, '|');
// 		ret[cnt] = ret_2[0];
// 		ret[cnt + 1] = ret_2[1];
// 		tmp = ret_2[1];
// 	}
// 	return (ret);
// }

// char **make_cmd_pipe(int pipe_num)
// {
//     int i = pipe_num;
//     int cnt = -1;
//     char *tmp;
//     char **ret;
//     char **ret_2;

//     ret = (char **)malloc(sizeof(char *) * (pipe_num + 1));
//     ret_2 = ft_split(g_glob.cmd, '|');
//     tmp = ret_2[1];

//     while (++cnt < i - 1)
//     {
//         ret[cnt] = ret_2[0];
//         ret_2 = ft_split(tmp, '|');
//         ret[cnt + 1] = ret_2[0];
//         tmp = ret_2[1];
//     }

//     ret[cnt] = ret_2[0];
//     ret[cnt + 1] = ret_2[1];

//     return ret;
// }
