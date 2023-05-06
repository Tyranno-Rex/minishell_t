#include "../../include/minishell.h"

char **ft_split_equal(char *s)
{
    char        **result;
    int         num = 1; 
    int         i = 1;
    
    result = ft_split(s, '=');
    while (result[++num])
    {
        result[1] = do_join(result[1], "=");
        result[1] = do_join(result[1], result[num]);
    }
    while (result[++i])
    {
        free(result[i]);
        result[i] = NULL;
    }
    return (result);
}

void check_list_add(t_token *ex_list, char *env_list)
{
	char 	**tmp;
	t_env 	*new_env;

	(void)ex_list;
    tmp = NULL;
	if (ft_strchr(env_list, '='))
	{
		tmp = ft_split_equal(env_list);
		printf("1. env key: %s\n env val : %s\n", tmp[0], tmp[1]);
		new_env = env_lstnew(tmp[0], tmp[1]);
		env_lstadd_back(&g_glob.env, new_env);
	}
    free(tmp);
}

void    ft_export(void)
{
    t_glob  tmp;
    t_env   *check;
	t_token	ex_list;
    char    **str;

    tmp = g_glob;
    tmp.tok = tmp.tok->next;
    while (tmp.tok)
    {
		if (tmp.tok->type == 1)
        {
            // 들어온 데이터의 값중 키값을 str[0] val값을 str[1]
            str = ft_split_equal(tmp.tok->data);
            // 키값과 같은 환경 변수 노드 찾기
            check = env_search_key(str[0]);
            if (!check)
			    check_list_add(&ex_list, tmp.tok->data);
            else
            {
                free(check->val);
                check->val = NULL;
                check->val = ft_strdup(str[1]);
            }
        }
        tmp.tok = tmp.tok->next;
    }
    free_matrix(str);
}