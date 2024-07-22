// // 자식 프로세스 생성함수
// #include "../../include/minishell.h"

// char    **check_argv(void)
// {
//     t_token *tmp;
//     int     cnt;
//     char    **av_argv;

//     tmp = g_glob.tok;
//     cnt = 0;
//     while (tmp)
//     {
//         tmp = tmp->next;
//         cnt++;
//     }
    
//     av_argv = calloc(cnt, sizeof(char *));
    
//     tmp = g_glob.tok;
//     if (!tmp)
//         return (NULL);
//     cnt = -1;
//     while (tmp)
//     {
//         av_argv[++cnt] = tmp->data;
//         tmp = tmp->next;
//     }
    
//     return (av_argv);
// }

// void ft_execve()
// {
// 	char    *command;
//     char    **command_all;
// 	char    *path;
//     int     path_n = 0;
	
// 	command = g_glob.tok->data;
//     command_all = check_argv();
// 	path = ft_strdup(g_glob.path[path_n]);
// 	while (path)
// 	{
// 		path = do_join(path, "/");
// 		path = do_join(path, command);
// 		if (access(path, F_OK))
// 			execve(path, command_all, g_glob.env_ori);
// 		path = ft_strdup(g_glob.path[path_n]);
// 		path++;
// 	}
// 	// exit(1);
// }

// void	child_builtin()
// {
//     char    *command;

//     command = g_glob.tok->data;
// 	env_2D();
// 	if (!is_builtin(command) && command)
// 	{
// 		printf("commad : %s", command);
// 		ft_execve();
// 	}
//     // echo랑 env pwd 와 같은 단순 출력 함수들은 파이프 뒤에 나와도 출력 처리해야 할 듯?
//     else if (command && !ft_strncmp(command, "pwd", 3))
//         ft_exec_cd();
// 	else if (is_builtin(command) && command && !ft_strncmp(command, "echo", 4))
//         ft_exec_echo();
// 	else if (is_builtin(command) && command && !ft_strncmp(command, "env", 3))
// 		ft_exec_echo();
// }


// // static void	*child_redir(int fd[2])
// // {
// // 	t_pipe 	*node;

// // 	node = g_glob.root->pipe;
// // 	printf("hello1\n");
// // 	if (node->infile != STDIN_FILENO)
// // 	{
// // 		if (dup2(node->infile, STDIN_FILENO) == -1)
// // 			printf("minishell: dup2 failed\n");
// // 		close(node->infile);
// // 	}
// // 	printf("hello2\n");
// // 	if (node->outfile != STDOUT_FILENO)
// // 	{
// // 		if (dup2(node->outfile, STDOUT_FILENO) == -1)
// // 			printf("minishell: dup2 failed\n");
// // 		close(node->outfile);
// // 	}
// // 	// else if (cmd->next && dup2(fd[1], STDOUT_FILENO) == -1)
// // 	else if (dup2(fd[1], STDOUT_FILENO) == -1)
// // 		printf("minishell: dup2 failed\n");
// // 	printf("hello3\n");
// // 	close(fd[1]);
// // 	return ("");
// // }

// static void	*child_redir(int fd[2])
// {
// 	t_pipe 	*node;

// 	node = g_glob.root->pipe;
// 	printf("hello1\n");
// 	if (node->infile != STDIN_FILENO)
// 	{
// 		if (dup2(node->infile, STDIN_FILENO) == -1)
// 			printf("minishell: dup2 failed\n");
// 		close(node->infile);
// 	}
// 	printf("hello2\n");
// 	if (node->outfile != STDOUT_FILENO)
// 	{
// 		if (dup2(node->outfile, STDOUT_FILENO) == -1)
// 			printf("minishell: dup2 failed\n");
// 		close(node->outfile);
// 	}
// 	printf("hello3\n");
// 	close(g_glob.root->pipe->fd[1]);
// 	return ("");
// }

// void	child_process(int fd[2])
// {
//     // 리다이렉션도 처리해야함.
// 	printf("hello0\n");
//     // child_redir(fd);
// 	printf("helloY\n");
// 	child_builtin();
// 	close(fd[1]);
// 	close(fd[0]);
// 	// child_free();
//     exit(EXIT_SUCCESS); // g_status로 변경해야함
// }

// void	exec_fork()
// {
// 	pid_t	pid;
// 	int		status;
// 	int		fd[2];

// 	pipe(fd);
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		close(fd[0]);
// 		close(fd[1]);
//         printf("ERROR FORK IS NOT SUCESS\n");
//         exit(EXIT_FAILURE); // 해당 내용 수정해야함.
// 	}
// 	else if (!pid) // 자식 프로세스면 실행
// 	{
// 		printf("child process execute\n");
// 		child_process(fd);
// 		exit(EXIT_SUCCESS);
// 	}	
// 	waitpid(pid, &status, 0);
//     // 이거 실행한 위치에서 waitpid 작성 필요
// }
