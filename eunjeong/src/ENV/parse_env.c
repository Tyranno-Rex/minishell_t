/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:57:08 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/04 18:23:31 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	parse_path(void)
{	// PATH 확인하기 쉽게 따로 g_glob.path에 이차원 배열로 저장
	char	**path;

	path = ft_split(env_search_key("PATH")->val, ':');
	if (!path)
		return (print_error("Fail to allocate memory: parse_path\n"));
	g_glob.path = path;
	return (TRUE);
}

t_bool	make_envnode(char *key, char *val)
{	// 환경변수 노드 생성 후 추가
	t_env	*new;

	new = env_lstnew(key, val);
	if (!new)
		return (FALSE);
	env_lstadd_back(&(g_glob.env), new);
	return (TRUE);
}

t_bool	env_list(char *k, char *v)
{	// 환경변수 노드 만들고 뒤에 추가
	char	*key;
	char	*val;

	key = ft_strdup(k);
	if (!key)
		return (FALSE);
	val = ft_strdup(v);
	if (!val)
	{
		free(key);
		return (FALSE);
	}
	if (!make_envnode(key, val))
		return (FALSE);
	return (TRUE);
}

t_bool	parse_env(char ***env)
{	// 환경변수 파싱: 연결리스트로 만들기
	int		i;
	char	**kv;

	i = -1;
	while ((*env)[++i])
	{
		kv = ft_split((*env)[i], '=');	// = 기준으로 분리
		if (!kv)
			return (print_error("Fail to allocate memory: parse_env\n"));
		if (!env_list(kv[0], kv[1]))	// 차례대로 환경변수 리스트에 넣기
		{
			env_lstclear(&(g_glob.env));
			return (print_error("Fail to allocate memory: env list\n"));
		}
		free_matrix(kv);	// ft_split()
	}
	if (!parse_path())	// PATH 따로 빼기
		return (FALSE);
	//env_lstprint();	// 환경변수 출력
	return (TRUE);
}
