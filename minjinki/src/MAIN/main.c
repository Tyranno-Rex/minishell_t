/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:02 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/05 14:33:02 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	while (TRUE)
	{
		print_pwd();	// 경로 맨 마지막 디렉토리 출력 -> 없애도 될 듯..
		g_glob.cmd = readline(" minishell_$ ");	// 프롬프트 출력
		if (!parse(g_glob.cmd))	// 명령 파싱
		{
			free_all();
			continue ;
		}
		free_cmd(g_glob.cmd);	// 이전 명령어 관련 변수 메모리 해제
		//exit(0);
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
	init_env(&env);	// 환경변수 초기화
	minishell();	// 프롬프트 입력 받기
	free_all();		// 전역변수 메모리 해제
	return (SUCCESS);
}
