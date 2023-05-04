#include "../../include/minishell.h"

// minishell에서 "pwd" 명령어를 처리하는 함수
int	ft_exec_pwd(void)
{
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

void	ft_exec_env(void)
{
	// 이 부분 파싱 부분 받아서 수정해야함
	int check_free_to_process = 0;

	// 인자 없이 "cd" 명령어를 입력한 경우 현재 작업 디렉토리 경로 출력
	if (check_free_to_process != 1)
		ft_env();
	else
	{
		// if (create_child_process() == 0)
		// {
		// 	ft_env(data->builtin_vars);
		// 	free_children_main(data, NULL);
		// 	exit(EXIT_SUCCESS);
		// }
		ft_env();
	}
}

int	ft_exec_cd(void)
{
	// 이 부분 파싱 부분 받아서 수정해야함
	int check_free_to_process = 0;

	// 인자 없이 "cd" 명령어를 입력한 경우 현재 작업 디렉토리 경로 출력
	if (check_free_to_process != 1)
		ft_cd();
	else
	{
		// if (create_child_process() == 0)
		// {
			// ft_cd(data);
			// exit(EXIT_SUCCESS);
		// }
		ft_cd();
	}
	return (0);
}

