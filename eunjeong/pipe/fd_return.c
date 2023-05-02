#include "../inc/minishell.h"

// 파일 디스크립터를 반환해서 해당 파일에서 작업을 진행
int get_fd(int oldfd, char *path, int flags[2])
{
	int fd;	// 가져온 파일 디스크립터를 저장할 변수
	
	
	// 이전 파일 디스크립터가 2보다 크다면, 닫는다.
	if (oldfd > 2)
		close(oldfd);
	// 파일 경로가 없다면 -1을 반환한다.
	if (!path)
		return (-1);
	
	// 파일에 대한 접근 권한이 X 또는 열 수 없음
	if (access(path, F_OK) == -1 && !flags[0])
		mini_perror(NDIR, path, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		mini_perror(NPERM, path, 126);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		mini_perror(NPERM, path, 126);
	
	// 파일 플래그를 확인하고 open 함수를 통해 파일 디스크립터 제공.
	
	// 파일에 내용 추가 <<
	if (flags[0] && flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	// 파일에 내용을 초기화 하고 추가 <
	else if (flags[0] && !flags[1])
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	// 가져온 파일 디스크립터를 반환한다.
	return (fd);
}


// 입출력 파일 가져오는 기본 예시 함수
// <
t_data	*infile_set1(t_data *node, char **args, int *i)
{
	char	*error_msg;	// 적절한 에러 메시지를 저장할 변수
	int		flags[2];	// 파일 플래그를 저장할 배열

	// 파일 플래그 초기화
	flags[0] = 1;
	flags[1] = 0;
	// 에러 메시지 초기화
	error_msg = "error! fd number get wrong value! error!'";
	(*i)++;	// i를 1 증가시킨다.
	if (args[*i])
		// 가져온 출력 파일 디스크립터를 node->outfile에 저장한다.
		node->outfile = get_fd(node->outfile, args[*i], flags);
	if (!args[*i] || node->outfile == -1)	// 가져온 디스크립터가 유효하지 않은 경우
	{
		*i = -1;	// i를 -1로 초기화한다.
		if (node->outfile != -1)	// 이미 파일 디스크립터를 가져온 경우
			ft_putendl_fd(error_msg, 2);	// 적절한 에러 메시지
	}
	return (node);
}

// 입출력 파일 가져오는 기본 예시 함수
// <<
t_data	*infile_set2(t_data *node, char **args, int *i)
{
	char	*error_msg;	// 적절한 에러 메시지를 저장할 변수
	char	*path;
	// 에러 메시지 초기화
	error_msg = "error! fd number get wrong value! error!'";
	(*i)++;	// i를 1 증가시킨다.
	if (args[*i])
	{
		//  infile에 str 출력해야하는 값을 저장한다. 
		
		path = args[*i];
		node->infile = get_heredoc(path);
	}
	if (!args[*i] || node->infile == -1)	// 가져온 디스크립터가 유효하지 않은 경우
	{
		*i = -1;	// i를 -1로 초기화한다.
		if (node->outfile != -1)	// 이미 파일 디스크립터를 가져온 경우
			ft_putendl_fd(error_msg, 2);	// 적절한 에러 메시지
	}
	return (node);
}