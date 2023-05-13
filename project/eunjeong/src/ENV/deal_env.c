/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:09:03 by MJKim             #+#    #+#             */
/*   Updated: 2023/05/13 10:50:05 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	deal_exit_stat(char **pre, char *next)
// {
// 	char	*stat;

// 	stat = ft_itoa(g_glob.exit_stat);
// 	*pre = do_join(*pre, stat);
// 	*pre = do_join(*pre, next);
// 	free(stat);
// }

/*
** 구분자 찾아서 그 까지의 부문자열 저장(key)
** key에 해당하는 환경변수 있다면 env에 해당 노드 저장, 없다면 NULL 저장
*/
int	get_env(char *s, t_env **env)
{
	int		i;
	int		len;
	char	*key;
	char	*target;

	i = -1;
	while (s[++i])
	{
		target = ft_strchr(" $.:\'\"", s[i]);
		if (target)
			break ;
	}
	if (!target)
		len = ft_strlen(s);
	else
		len = ft_strchr(s, target[0]) - s;
	key = ft_strndup(s, len);
	if (!key)
		return (ERROR);
	*env = env_search_key(key);
	free(key);
	return (len);
}

int	deal_exit_stat(t_token *cur, char **tmp, int i)
{
	int		len;
	char	*stat;

	stat = ft_itoa(g_glob.exit_stat);
	*tmp = do_join(*tmp, stat);
	*tmp = do_join(*tmp, cur->data + i + 1);
	len = ft_strlen(stat);
	free(stat);
	return (len);
}

int	deal_dollar_sign(t_token *cur, char **tmp, int *i)
{
	int		len;
	t_env	*env;

	*tmp = ft_strndup(cur->data, (*i)++);
	if (!*tmp)
		return (FALSE);
	if (cur->data[*i] == '?')
		len = deal_exit_stat(cur, tmp, *i);
	else
	{
		len = get_env(cur->data + (*i), &env);
		if (len == ERROR)
			return (ERROR);
		if (env)
		{
			*tmp = do_join(*tmp, env->val);
			if (!*tmp)
				return (FALSE);
		}
	}
	return (len);
}

/*
** 환경변수 치환 함수
*/
t_bool	convert_env(t_token *cur)
{
	int		i;
	int		len;
	char	*tmp;

	if (!cur)
		return (TRUE);
	if ((cur->type == STR || cur->type == DOUBLE || cur->type == TMP))
	{
		i = -1;
		while (cur->data[++i])
		{
			while (cur->data[i] && cur->data[i] != '$')
				i++;
			if (!(cur->data[i]))
				break ;
			len = deal_dollar_sign(cur, &tmp, &i);
			tmp = do_join(tmp, &(cur->data[i + len]));
			free(cur->data);
			cur->data = tmp;
			i += len - 1;
		}
	}
	return (TRUE);
}

// t_bool	join_n_split(t_token *token)
// {
// 	int		i;
// 	char	*data;
// 	char	**matrix;
// 	t_token	*tmp;
// 	t_token	*new;

// 	new = NULL;
// 	while (token)
// 	{
// 		matrix = ft_split(token->data, ' ');
// 		if (!matrix)
// 			return (FALSE);
// 		i = -1;
// 		while (matrix[++i])
// 		{
// 			data = ft_strdup(matrix[i]);
// 			if (!data)
// 				return (FALSE);
// 			tmp = ft_lstnew(STR, data);
// 			if (!tmp)
// 				return (FALSE);
// 			ft_lstadd_back(&(new), tmp);
// 			if (matrix[i+1])
// 			{
// 				tmp = ft_lstnew(SPACES, NULL);
// 				if (!tmp)
// 					return (FALSE);
// 				ft_lstadd_back(&(new), tmp);
// 			}
// 		}
// 		ft_lstclear(&(g_glob.tok));
// 		g_glob.tok = new;
// 		free_matrix(matrix);
// 		token = token->next;
// 	}

// 	return (TRUE);
// }

// void   remove_spaces(t_token *token)
// {
//    t_token   *pre;
//    t_token   *next;

//    pre = NULL;
//    while (token)
//    {
//       while (!pre && token->type == SPACES) 
//       {
//          next = token;
//          token = token->next;
//          ft_lstdelone(next);
//          token = token->next;
//       }
//       next = token->next;
//       if (token->next && token->type != SPACES && token->next->type == SPACES)
//       {
//          next = token->next;
//          token->next = next->next;
//          ft_lstdelone(next);
//          pre = token;
//          token = token->next;
//       }
//       else
//       {
//       pre = token;
//       token = token->next;
//       }
//    }
// }

// void   remove_spaces(t_token *token)
// {
// //    char   *tmp;
//    t_token   *pre;
//    t_token   *next;

//    pre = NULL;
//    while (token)
//    {
//       while (!pre && token->type == SPACES)   // 맨 앞에 나온 SPACES node 삭제
//       {
//          next = token;
//          token = token->next;
//          ft_lstdelone(next);
//          token = token->next;
//       }
//       next = token->next;
//       if (token->next && token->type != SPACES && token->next->type == SPACES)
//       {
//          next = token->next;
//          token->next = next->next;
//          ft_lstdelone(next);
//          pre = token;
//          token = token->next;
//       }
//    }
// }

// void	remove_spaces(t_token *token)
// {
// 	char	*tmp;
// 	t_token	*pre;
// 	t_token	*next;

// 	pre = NULL;
// 	while (token)
// 	{
// 		while (!pre && token->type == SPACES)	// 맨 앞에 나온 SPACES node 삭제
// 		{
// 			next = token;
// 			token = token->next;
// 			ft_lstdelone(next);
// 			token = token->next;
// 		}
// 		next = token->next;
// 		if (token->next && token->type != SPACES && token->next->type != SPACES)
// 		{	// 아 이거 STR이랑 TMP? 로 구분해야 할 듯
// 			tmp = ft_strjoin(token->data, next->data);
// 			free(token->data);
// 			token->data = tmp;
// 			token->next = next->next;
// 			ft_lstdelone(next);
// 		}
// 		else if (token->next && token->type != SPACES && token->next->type == SPACES)
// 		{
// 			next = token->next;
// 			token->next = next->next;
// 			ft_lstdelone(next);
// 			pre = token;
// 			token = token->next;
// 		}
// 	}
// }

t_bool	deal_env(t_token **token)
{
	t_token	*cur;

	cur = *token;
	while (cur)
	{
		if (!convert_env(cur))
			return (FALSE);
		cur = cur->next;
	}
	return (TRUE);
}
