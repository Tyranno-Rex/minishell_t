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
    if (!tmp)
        return (NULL);
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

    char    *command;
    char    **command_all;
    // char    **path;
    char    *path;
    pid_t   pid;
    int     number = 0;
    int     path_n = 0;
    int     fd[2];

	env_2D();
    command = g_glob.tok->data;
    command_all = check_argv();
    pipe(fd);
    pid = fork();
    path = ft_strdup(g_glob.path[path_n]);
    if (!pid)
    {
        close (fd[0]);
        dup2(fd[1], STDERR_FILENO);
        close(fd[1]);
        while (path)
        {
            path = do_join(path, "/");
            path = do_join(path, command);
            if (!access(path,F_OK))
                number = execve(path, command_all, g_glob.env_ori);
            path = ft_strdup(g_glob.path[path_n]);
            path_n++;
        }
        exit(1);
    }
    // free(command);
    // free_matrix(command_all);
    free(path);
    close(fd[1]);
    waitpid(pid, NULL, 0);
    close(fd[0]);
    if (number == -1)
    {
        g_glob.exit_stat = 126;
    }
}

// void    ft_execve(void)
// {

//     char    *command;
//     char    **command_all;
//     char    **path;
//     pid_t   pid;
//     int     number = 0;
//     int     path_n = 0;
//     int     fd[2];

// 	env_2D();
//     command = g_glob.tok->data;
//     command_all = check_argv();
//     path = g_glob.path;
//     pipe(fd);
//     pid = fork();
//     if (!pid)
//     {
//         close (fd[0]);
//         dup2(fd[1], STDERR_FILENO);
//         close(fd[1]);
//         while (path[path_n])
//         {
//             path[path_n] = do_join(path[path_n], "/");
//             path[path_n] = do_join(path[path_n], command);
//             if (!access(path[path_n],F_OK))
//                 number = execve(path[path_n], command_all, g_glob.env_ori);
//             path_n++;
//         }
//         exit(1);
//     }
//     // free(command);
//     // free_matrix(command_all);
//     free_matrix(path);
//     close(fd[1]);
//     waitpid(pid, NULL, 0);
//     close(fd[0]);
//     if (number == -1)
//     {
//         g_glob.exit_stat = 126;
//     }
// }

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