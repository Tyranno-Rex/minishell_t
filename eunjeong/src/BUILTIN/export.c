#include "../../include/minishell.h"


void check_list_add(t_token *ex_list, char *env_list)
{
	char 	**tmp;
	t_env 	*new_env;

	(void)ex_list;
	if (ft_strchr(env_list, '='))
	{
		tmp = ft_split(env_list, '=');
		printf("1. env key: %s\n env val : %s\n", tmp[0], tmp[1]);
		new_env = env_lstnew(tmp[0], tmp[1]);
		env_lstadd_back(&g_glob.env, new_env);
	}

}

void    ft_export(void)
{
    t_glob  tmp;
	t_token	ex_list;
		
    tmp = g_glob;
    while (tmp.tok)
    {
		if (tmp.tok->type == 1)
			check_list_add(&ex_list, tmp.tok->data);
        tmp.tok = tmp.tok->next;
    }
}