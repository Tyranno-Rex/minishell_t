/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:02 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/11 13:19:01 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void sig_handler(int signal)
{
    if (signal == SIGINT)
    {
        printf("\033[K"); //지워버리는 것을 원하지는 않았음.
        printf("nanoshell$ \n");
    }

    if (rl_on_new_line() == -1) // readline으로 설정한 문자열을 한 번 출력한다?
        exit(1);
    rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다.
    rl_redisplay();         // 프롬프트 커서가 움직이지 않게 해준다.
}

void setting_signal()
{
    signal(SIGINT, sig_handler); // CTRL + C
    signal(SIGQUIT, SIG_IGN);    // CTRL + /
                                 // signal(SIGTERM, sig_handler);
}

void	init_rl_catch_signals(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
}

void	print_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);	// 현재 경로 얻기
	// 맨 마지막 /
	ft_putstr_fd(ft_strrchr(pwd, '/') + 1, 1);
	free(pwd);
}

void	minishell(void)
{
	setting_signal();
	init_rl_catch_signals();
	if (g_glob.env)
		env_lstprint();
	while (TRUE)
	{
		print_pwd();	// 경로 맨 마지막 디렉토리 출력 -> 없애도 될 듯..
		g_glob.cmd = readline(" minishell_$ ");	// 프롬프트 출력
		if (!g_glob.cmd)
			return ;
		if (!parse(g_glob.cmd))	// 명령 파싱
		{
			free_cmd(g_glob.cmd);
			continue ;
		}
		//env_lstprint();
		free_cmd(g_glob.cmd);	// 이전 명령어 관련 변수 메모리 해제
	}
}

void	check_leaks(void)
{
	system("leaks --list minishell");
}

int	main(int ac, char **av, char **env)
{
	atexit(check_leaks);
	(void)av;
	if (ac != 1)
		exit_with_code("usage: ./minishell\n", 126);
	ft_bzero(&(g_glob), sizeof(g_glob));
	init_env(&env);	// 환경변수 초기화
	minishell();	// 프롬프트 입력 받기
	free_all();		// 전역변수 메모리 해제
	return (SUCCESS);
}
