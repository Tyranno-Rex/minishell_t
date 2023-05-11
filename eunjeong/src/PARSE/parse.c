/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:56 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/11 14:52:48 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	is_space_only(char *cmd)
{	// 명령어 공백인 경우
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_is_space(cmd[i]))
			return (FALSE);
	}
	return (TRUE);
}

t_bool	parse(char *cmd)
{	// 엔터만 입력한 경우, 공백만 들어온 경우 바로 반환 -> 이 경우는 히스토리에 저장되지 않음
	if (ft_strlen(cmd) == 0 || is_space_only(cmd))
		return (FALSE);
	add_history(g_glob.cmd);	// 명령어 히스토리 저장
	if (!deal_quotes(cmd, -1) || !deal_spaces())
	// 1. 따옴표 단위로 구분 후 2. 공백 단위로 구분
		return (FALSE);
	if (!deal_pipe_n_redi()) // 파이프, 리다이렉션 문자 분리
		return (FALSE);
	if (!set_pipe_n_redi())	// 파이프, 리다이렉션 구문 에러 확인
		return (FALSE);
	if (!deal_env(&(g_glob.tok)))	// 환경변수 치환
		return (FALSE);
	//ft_lstprint(& (g_glob.tok));
	if (!chk_cmd_is_valid()) // syntax error
		return (FALSE); // return TRUE
	if (!merge_n_split_nodes(&(g_glob.tok)))
		return (FALSE);
	ft_lstprint(&(g_glob.tok));
	// if (!init_tree())
	// 	return (FALSE);
	return (TRUE);
}
// should add error handling
