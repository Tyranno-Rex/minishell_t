#include "../../include/minishell.h"
char    **make_tok2D(t_token *block)
{
    t_token *tmp;
    int     cnt;
    char    **av_argv;

    tmp = block;
    cnt = 0;
    while (tmp)
    {
        if (tmp->type == SPACES)
            cnt += 0;
        else
            cnt += 1;
        tmp = tmp->next;
    }
    av_argv = ft_calloc(cnt + 1, sizeof(char *));
    tmp = block;
    if (!tmp)
        return (NULL);
    cnt = -1;
    while (tmp)
    {
        if (tmp->type == SPACES)
            cnt += 0;
        else
            av_argv[++cnt] = ft_strdup(tmp->data);
        tmp = tmp->next;
    }
    cnt = -1;
    return (av_argv);
}

void printf_2d(char **s)
{
    int i = -1;
    while (s[++i])
        printf("%s\n", s[i]);
}
void    ft_execve(t_token *block)
{

    char    *command;
    char    **command_all;

    char    *path;
    pid_t   pid;
    int     number = 0;
    int     path_n = 0;
    int     fd[2];

	env_2D();
    command = block->data;
    command_all = make_tok2D(block);
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
    free_matrix(command_all);
    free(path);
    close(fd[1]);
    waitpid(pid, NULL, 0);
    close(fd[0]);
    if (number == -1)
    {
        g_glob.exit_stat = 126;
    }
}
// void    ft_execve(t_token *block)
// {
//     char    *command;
//     char    **command_all;
//     int     fd[2];
//     pid_t   pid;
//     char    *path;
//     int     path_n = 0;

//     printf("!\n");
// 	env_2D();
//     command = block->data;
//     command_all = make_tok2D(block);
//     printf("!\n");
//     path = ft_strdup(g_glob.path[path_n]);
//     printf("!\n");
//     pipe(fd);
//     pid = fork();
//     if (!pid)
//     {
//         // dup2(open_fd, STDOUT_FILENO);
//         // close(open_fd);
//         close(fd[0]);
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[1]);
//         close(fd[1]);
//         while (path)
//         {
//             path = do_join(path, "/");
//             path = do_join(path, command);
//             if (!access(path, F_OK))
//             {
//                 printf("hello3\n");
//                 execve(path, command_all, g_glob.env_ori);
//                 printf("hello4n");
//             }
//             path = ft_strdup(g_glob.path[path_n]);
//             path_n++;
//         }
//         exit(1);
//     }
//     // free_matrix(command_all); // 2개 이상의 문장이 들어가면 더블프리현상이 발생함.
//     free(path);
//     close(fd[1]);
//     close(fd[0]);
//     waitpid(pid, NULL, 0);
// }
