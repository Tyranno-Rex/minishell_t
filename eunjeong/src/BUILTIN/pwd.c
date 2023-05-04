#include "../../include/minishell.h"

// 현재 작업 디렉토리 경로를 가져와서 표준 출력에 출력하는 함수
void	ft_pwd(void)
{
	// 현재 작업 디렉토리 경로를 저장할 포인터
	char		*current_path;

	// getcwd() 함수를 사용하여 현재 작업 디렉토리 경로를 가져옴
	current_path = getcwd(NULL, 0);

	// 경로가 NULL일 경우 "error" 출력
	if (!current_path)
		printf("error");
	
	// 경로가 유효할 경우 경로 출력 후 메모리 해제
	else
	{
		printf("%s", current_path);
		free(current_path);
	}
	printf("\n");
}
