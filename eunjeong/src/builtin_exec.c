#include "../inc/minishell.h"

// minishell에서 "pwd" 명령어를 처리하는 함수
int	ft_exec_pwd(char **data)
{
	// 인자로 들어온 data 포인터는 구문 분석 결과를 담은 구조체이므로, 
	// 이 함수에서는 사용하지 않음
	(void) data;
	// 이 부분 파싱 부분 받아서 수정해야함
	int check_free_to_process = 0;

	// 인자 없이 "pwd" 명령어를 입력한 경우 현재 작업 디렉토리 경로 출력
	if (check_free_to_process != 1)
		ft_pwd();
	// 인자가 있는 경우 자식 프로세스 생성 후 현재 작업 디렉토리 경로 출력
	else
	{
		// if (create_child_process() == 0)
		// {
		// 	ft_pwd();
		// 	exit(EXIT_SUCCESS);
		// }
		ft_pwd();
	}

	// 함수 종료
	return (0);
}


int	ft_exec_cd(char **data)
{
	(void) data;
	// 이 부분 파싱 부분 받아서 수정해야함
	int check_free_to_process = 0;

	// 인자 없이 "cd" 명령어를 입력한 경우 현재 작업 디렉토리 경로 출력
	if (check_free_to_process != 1)
		ft_cd(data);
	else
	{
		// if (create_child_process() == 0)
		// {
			// ft_cd(data);
			// exit(EXIT_SUCCESS);
		// }
		ft_cd(data);
	}
	return (0);
}