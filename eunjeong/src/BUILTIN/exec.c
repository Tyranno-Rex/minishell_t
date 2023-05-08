#include "../../include/minishell.h"

char    **check_argv(void)
{
    t_token *tmp;
    int     cnt;
    char    **av_argv;

    tmp = g_glob.tok;
    cnt = 0;
    while (tmp)
    {
        tmp = tmp->next;
        cnt++;
    }
    
    av_argv = calloc(cnt, sizeof(char *));
    
    tmp = g_glob.tok;
    tmp = tmp->next;
    cnt = -1;
    while (tmp)
    {
        av_argv[++cnt] = tmp->data;
        tmp = tmp->next;
    }
    return (av_argv);
}

void    ft_execve(void)
{

    char    **command;
    char    **path;
    int     number = 0;
    int     path_n = -1;

	env_2D();
    command = check_argv();
    path = g_glob.path;

	if (!is_builtin(command[0]) && command)
    {
        char *test = ft_strdup(command[0]);
        path[path_n] = ft_strjoin(path[path_n], test);
        // path[path_n] = do_join(path[path_n], test);
        printf("command is enterd: %s\n", command[0]);
        while (path[++path_n])
        {
            printf("path name : %s\n", path[path_n]);
            number = execve(path[path_n], command, g_glob.env_ori);
            if (number != -1)
                break;
        }
    }

    if (number == -1)
    {
        while (command[++number])
            printf("bash: %s: command not found\n", command[number]);     
        g_glob.exit_stat = 126;
    }
}















// void    ft_execve(void)
// {

//     char    *command;
//     int     number;

// 	env_2D();
//     command = g_glob.tok->data;
// 	if (!is_builtin(command) && command)
//     {
//         printf("command is enterd: %s\n", command);
//         number = execve(*g_glob.path, &command, g_glob.env_ori);
//     }
//     if (number == -1)
//     {
//         printf("bash: %s: command not found", command);
//         g_glob.exit_stat = 126;
//     }
// }