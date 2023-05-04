#include "minishell.h"

/*
** 파일 또는 디렉토리가 존재하지 않거나 접근 권한이 없거나 디렉토리가 아닐 경우
** 에러 메시지를 출력하는 함수
*/
void	cd_error(char *path)
{
	ft_putstr_fd("Minishell: cd: ", 2); // 에러 메시지 출력
	ft_putstr_fd(path, 2); // 경로 출력
	if (access(path, F_OK) == -1) // 파일 또는 디렉토리가 존재하지 않을 경우
		ft_putendl_fd(": no such file or directory", 2); // 에러 메시지 출력
	else if (access(path, R_OK) == -1) // 읽기 권한이 없을 경우
		ft_putendl_fd(": permission denied", 2); // 에러 메시지 출력
	else // 그 외의 경우 (디렉토리가 아닐 경우)
		ft_putendl_fd(": not a directory", 2); // 에러 메시지 출력
	g_data.status = 256; // 전역 변수 status에 256 저장
}

/*
** 디렉토리를 변경하는 함수
*/
void	change_dir(char *path, int print_path)
{
	char	*cwd; // 현재 작업 디렉토리를 저장할 변수
	char	buff[4097]; // 작업 디렉토리를 저장할 버퍼
	int		ch; // chdir() 함수의 리턴값을 저장할 변수

	cwd = getcwd(buff, 4096); // 현재 작업 디렉토리를 가져옴
	set_env_var("OLDPWD", ft_strdup(cwd)); // 이전 작업 디렉토리를 저장함
	ch = chdir(path); // 작업 디렉토리를 변경함
	if (!ch && cwd) // 작업 디렉토리를 변경하는 데 성공했을 경우
	{
		cwd = getcwd(buff, 4096); // 변경된 작업 디렉토리를 가져옴
		set_env_var("PWD", ft_strdup(cwd)); // 작업 디렉토리를 저장함
		if (print_path) // print_path가 참일 경우
			ft_putendl_fd(get_env_var("PWD"), 1); // 작업 디렉토리를 출력함
		g_data.status = 0; // 전역 변수 status에 0 저장 (성공)
	}
	else if (cwd) // 작업 디렉토리를 변경하는 데 실패했을 경우
		cd_error(path); // 에러 메시지를 출력함
	else if (!cwd && path[0] == '.' && path[1] == '\0') // 경로가 "."인 경우
		ft_putendl_fd("getcwd: cannot access parent directories: \
No such file or directory", 2); // 에러 메시지를 출력함
	return ; //
}


void cd(char **args)
{
    char *home_path;

    // get_env_var 함수를 사용하여 HOME 환경 변수 값을 가져옴
    home_path = get_env_var("HOME");

    // 인자가 없는 경우, cd ~ 와 같이 HOME 디렉토리로 이동
    if (!args[0])
        return (change_dir(home_path, 0));
    else
    {
        // -- 옵션이 주어진 경우, cd -- 와 같이 HOME 디렉토리로 이동
        if (ft_strequ(args[0], "--"))
            return (change_dir(home_path, 0));

        // - 옵션이 주어진 경우, cd - 와 같이 이전 디렉토리로 이동
        else if (args[0][0] == '-' && !args[0][2])
            return (change_dir(get_env_var("OLDPWD"), 1));

        // 인자가 주어진 경우, 해당 디렉토리로 이동
        return (change_dir(args[0], 0));
    }
}