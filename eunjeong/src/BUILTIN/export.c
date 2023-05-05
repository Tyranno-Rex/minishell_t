#include "../../include/minishell.h"


void    ft_export(void)
{
    while (g_glob.tok)
    {
        printf("env token : %s\n", g_glob.tok->data);
        g_glob.tok = g_glob.tok->next;
    }
}