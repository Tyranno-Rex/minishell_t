#include "../../include/minishell.h"


void    ft_export(void)
{
    while (g_glob.tok)
    {
        printf("env token : %s\n", g_glob.tok->data);
        g_glob.tok = g_glob.tok->next;
    }
    // input
    // ft_lstadd_back(&g_glob.env, input);
}

// void	ft_env(void)
// {
// 	t_env *tmp_env;
// 	tmp_env = g_glob.env;
// 	while (tmp_env)
// 	{
// 		printf("%s=%s\n", tmp_env->key, tmp_env->val);
// 		tmp_env = tmp_env->next;
// 	}
// }
