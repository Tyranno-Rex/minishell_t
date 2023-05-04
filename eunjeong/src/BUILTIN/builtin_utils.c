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