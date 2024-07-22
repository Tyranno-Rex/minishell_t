#include "../../include/minishell.h"

void    print_export_only()
{
    t_env *env;

    env = g_glob.env;
    while (env)
	{
		printf("declare -x %s=%s\n", env->key, env->val);
		env = env->next;
	}
}

int can_split(char *s)
{
    int i;

    i = -1;
    if (*s == '\0')
        return (0);
    while (s[++i])
    {
        if (s[i] == '=')
        {
            if ((i > 1 && s[i-1]) && s[i+1])
                return (0);
        }
    }
    return (1);
}

char **ft_split_equal(char *s)
{
    char        **result;
    int         num = 1; 
    int         i = 1;
    

    if (!ft_strchr(s, '=') || can_split(s))
    {
        printf("export: \'%s\': not a valid identifier\n", s);
        g_glob.exit_stat = 1;
        return (NULL);
    }       
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
   char    **tmp;
   t_env    *new_env;

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

void    ft_export(t_token *block)
{
    t_token  *tmp;
    t_env   *check;
    t_token   ex_list;
    char    **str;

    tmp = block;
    tmp = tmp->next;
    if (tmp == NULL)
        return print_export_only();
    while (tmp)
    {
      if (tmp->type != SPACES)
        {
            // 들어온 데이터의 값중 키값을 str[0] val값을 str[1]
            str = ft_split_equal(tmp->data);
            if (!str)
                return ;
            // 키값과 같은 환경 변수 노드 찾기
            check = env_search_key(str[0]);
            if (!check)
             check_list_add(&ex_list, tmp->data);
            else
            {
                free(check->val);
                check->val = NULL;
                check->val = ft_strdup(str[1]);
            }
        }
        tmp = tmp->next;
    }
    free_matrix(str);
}