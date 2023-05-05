#include "../../include/minishell.h"

// void	env_select_clear(char *env_value)
// {
// 	char *new_env_key;

// 	while (g_glob.env)
// 	{
// 		if (g_glob.env->key == env_value)
// 		{
// 			if (g_glob.env->next)
// 			{
// 				new_env_key = g_glob.env->next->key;
				
//                 free(g_glob.env);
// 				g_glob = g_glob;

// 			}
// 			else
// 				free(g_glob.env);
// 		}
// 		g_glob.env = g_glob.env->next;
// 	}
// }

// void check_list_del(char *env_list)
// {
// 	t_glob		tmp;

// 	tmp = g_glob;
// 	while (tmp.env)
// 	{
// 		if (!strncmp(tmp.env->key, env_list, ft_strlen(env_list)))
// 		{
// 			env_select_clear(env_list);
// 			break;
// 		}
// 		tmp.env = tmp.env->next;
// 	}	
// }

// void    ft_unset(void)
// {
//     t_glob  tmp;
//     int     count = 0;

		
//     tmp = g_glob;
//     while (tmp.tok)
//     {
// 		if (tmp.tok->type == 1 && count < 1)
// 			count++;
// 		else if (tmp.tok->type == 1 && count >= 1)
// 			check_list_del(tmp.tok->data);
//         tmp.tok = tmp.tok->next;
//     }
// }

void	ft_unset(void)
{
	t_env	*node;
	t_env	*pre;
	t_token	*tok;

	tok = g_glob.tok->next;
	while (tok)
	{
		pre = NULL;
		node = g_glob.env;
		while (node)
		{
			if (ft_strcmp(tok->data, node->key) == 0)
			{
				printf("tok->data: %s\n", tok->data);
				env_remove(pre, node);
				break ;
			}
			pre = node;
			node = node->next;
		}
		tok = tok->next;
	}
}