/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:16:58 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/05 16:23:19 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_lstprint(void)
{	// 환경변수 연결리스트 출력
	t_env	*cur;

	cur = g_glob.env;
	while (cur)
	{
		printf("key: %s\n", cur->key);
		printf("val: %s\n", cur->val);
		printf("--------------------------------------\n");
		cur = cur->next;
	}
}

t_env	*env_lstlast(t_env *lst)
{	// 환경변수 맨 마지막 노드 찾기
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{	// 환경변수 리스트 마지막에 노드 추가
	if (!lst || !new)
		return ;
	else if (!*lst)
		*lst = new;
	else
		env_lstlast(*lst)->next = new;
}

t_env	*env_lstnew(char *key, char *value)
{	// 환경변수 리스트의 노드 생성
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->val = value;
	new->next = NULL;
	return (new);
}

t_bool	env_lstclear(t_env **lst)
{	// 환경변수 리스트 삭제
	t_env	*cur;
	t_env	*tmp;

	if (!lst)
		return (TRUE);
	cur = *lst;
	if (!cur)
		return (TRUE);
	while (cur)
	{
		tmp = cur->next;
		if (cur->key)
			free(cur->key);
		if (cur->val)
			free(cur->val);
		free(cur);
		cur = tmp;
	}
	return (FALSE);
}
