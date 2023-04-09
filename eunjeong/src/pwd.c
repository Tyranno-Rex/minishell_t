#include "../inc/minishell.h"

void	exit_child(int sig)
{
	if (sig == SIGINT)
		printf("%s", "");
	if (sig == SIGQUIT)
		printf("QUIT");
}


// 자식 프로세스 생성 함수
pid_t	create_child_process(void)
{
	// 자식 프로세스의 pid 저장 변수
	pid_t	pid;

	// 시그널 핸들러 등록
	signal(SIGINT, exit_child);
	signal(SIGQUIT, exit_child);

	// fork() 함수를 사용하여 자식 프로세스 생성
	pid = fork();

	// 자식 프로세스 생성 실패 시 오류 출력 후 프로그램 종료
	if (pid < 0)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}

	// 자식 프로세스인 경우 pid 반환
	return (pid);
}

// 현재 작업 디렉토리 경로를 가져와서 표준 출력에 출력하는 함수
void	ft_pwd(void)
{
	// 현재 작업 디렉토리 경로를 저장할 포인터
	char		*current_path;

	// getcwd() 함수를 사용하여 현재 작업 디렉토리 경로를 가져옴
	current_path = getcwd(NULL, 0);

	// 경로가 NULL일 경우 "error" 출력
	if (!current_path)
	{
		printf("error");
	}
	// 경로가 유효할 경우 경로 출력 후 메모리 해제
	else
	{
		ft_putstr_fd(current_path, 1);
		free(current_path);
	}

	// 개행 문자 출력
	ft_putstr_fd("\n", 1);
}
