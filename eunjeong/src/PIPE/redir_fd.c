#include "../../include/minishell.h"

void error_print(int ERR_TYPE)
{
	if (ERR_TYPE == 1)
		printf("NO such file or dir");
	if (ERR_TYPE == 2)
		printf("NO perrmision to acess");
	free_all();
	exit(SUCCESS);
}



int	get_fd(int oldfd, char *path, int flags[2])
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		error_print(1);
	else if (!flags[0] && access(path, R_OK) == -1)
		error_print(2);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		error_print(2);
	// 1. flag(1, 1) 내용 추가
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	// 2. flag(1, 0) 새로운 내용을 생성
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	// 3.flag(0, 0) 해당 문서에서 읽어옴
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

void	outfile_set2(t_glob tmp)
{
	int		flags[2];


	// 1. flag (1, 1) 내용 추가
	flags[0] = 1;
	flags[1] = 1;

	// 다음 인수에 대해서 프로세스 처리를 진행하기 위해서 다음 명령어를 가져옴
	while (tmp.tok->type != 1)
		tmp.tok = tmp.tok->next;
	if (tmp.tok)
		g_glob.root->pipe->fd[1] = get_fd(g_glob.root->pipe->fd[1], tmp.tok->data, flags);
	if (!tmp.tok || g_glob.root->pipe->fd[1] == -1)
	{
		// *i = -1; 밖에 인자에게 해당 과정에 에러가 존재한다고 알릴 다른 방법이 필요함.
		if (g_glob.root->pipe->fd[1] != -1)
			printf("ERROR"); // 해당 상황은 파일을 못읽었을때
		else
			printf("ERROR"); // 해당 상황은 리다이렉션 뒤에 알맞은 인자가 없는 경우
	}
}


void	redir_fd(void)
{
	t_glob	tmp;

	tmp = g_glob;
	while (tmp.tok)
	{
		if (!strncmp(tmp.tok->data, "|", 1))
		{
			printf("test | : %s", tmp.tok->data);
			// exec_fork();
		}
		if (!strncmp(tmp.tok->data, ">>", 2))
		{
			printf("test >> : %s\n", tmp.tok->data);
			outfile_set2(tmp); 
		}
		else if (!strncmp(tmp.tok->data, ">", 1))
		{
			printf("test > : %s\n", tmp.tok->data);
			// outfile_set1(); 
		}
		else if (!strncmp(tmp.tok->data, "<<", 2))
		{
			printf("test << : %s\n", tmp.tok->data);
			// infile_set2();
		}
		else if (!strncmp(tmp.tok->data, "<", 1))
		{
			printf("test < : %s\n", tmp.tok->data);
			// infile_set1(); 
		}
		tmp.tok = tmp.tok->next;
	}
}