/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_scmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:58:01 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/02 16:45:55 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_scmd	add_scmd(t_token *token)
{
	t_scmd	*scmd;
	t_token	*start;

	scmd = NULL;
	start = token;
	if (token)
	{
		scmd = ft_calloc(1, sizeof(t_scmd));
		// scmd에 CMD만 (strdup 사용) -> 현재 노드만
		// opt에 CMD 다음 OPT 넣기.. (-로 시작하는 것들)
		// ori에 cmd 전체(e.g. echo -n a b c" d") -> strjoin
		//	-> 중복은 지우고 중복 아닌 건 join으로 합쳐서 -abc... 형태로
		// av에는 OPT 이하 ARGV들 저장
	}
	return (scmd);
}
