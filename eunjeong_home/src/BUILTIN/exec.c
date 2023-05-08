#include "../../include/minishell.h"

void    ft_execve(void)
{
    env_2D();
    // execve(*g_glob.path, &g_glob.tok->data, &g_glob.env_2D);
    printf("execve\n");
}