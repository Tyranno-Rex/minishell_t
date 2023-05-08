// 자식 프로세스 생성함수
#include "../../include/minishell.h"

void	child_builtin()
{
    char    *command;

    command = g_glob.tok->data;
    // 디폴트 시그널 처리(기존의 시그널 처리를 이어함
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	// filepath 에 대해서 공부해야겠음
	env_2D();

	if (!is_builtin(command) && command)
        execve(*g_glob.path, &command, g_glob.env_ori);

    // echo랑 env pwd 와 같은 단순 출력 함수들은 파이프 뒤에 나와도 출력 처리해야 할 듯?
    else if (command && !ft_strncmp(command, "pwd", 3))
        ft_exec_cd();
	else if (is_builtin(command) && command && !ft_strncmp(command, "echo", 4))
        ft_exec_echo();
	else if (is_builtin(command) && command && !ft_strncmp(command, "env", 3))
		ft_exec_echo();
}

void	*child_process()
{
    // 리다이렉션도 처리해야함.
    // child_redir();
	child_builtin();
	// child_free();
    exit(EXIT_SUCCESS);
}

void	exec_fork()
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		close(g_glob.root->pipe->fd[0]);
		close(g_glob.root->pipe->fd[1]);
        printf("ERROR FORK IS NOT SUCESS\n");
        exit(EXIT_FAILURE); // 해당 내용 수정해야함.
	}
	else if (!pid) // 자식 프로세스면 실행
	{
		printf("child process execute\n");
		child_process();
		exit(EXIT_SUCCESS);
	}	
	waitpid(pid, &status, 0);
    // 이거 실행한 위치에서 waitpid 작성 필요
}