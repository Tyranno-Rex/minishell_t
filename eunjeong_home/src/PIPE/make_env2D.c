#include "../../include/minishell.h"


void    env_2D(void)
{
    t_glob  tmp;
    
    tmp = g_glob;
    while (tmp.env)
    {
        g_glob.env_2D = ft_strjoin(tmp.env->key, "=");
        g_glob.env_2D = ft_strjoin(env_2D, g_glob.env_2D);
        tmp.env = tmp.env->next;
    }
}