#include "../../include/minishell.h"

char    **make_tok2D(void)
{
    t_glob  tmp;
    int     cnt;
    char    **av_argv;

    tmp = g_glob;
    cnt = 0;
    while (tmp.tok)
    {
        tmp.tok = tmp.tok->next;
        cnt++;
    }
    
    av_argv = ft_calloc(cnt + 1, sizeof(char *));
    
    tmp.tok = g_glob.tok;
    if (!tmp.tok)
        return (NULL);
    cnt = -1;
    while (tmp.tok)
    {
        av_argv[++cnt] = ft_strdup(tmp.tok->data);
        tmp.tok = tmp.tok->next;
    }
    return (av_argv);
}

void printf_2d(char **s)
{
    int i = -1;
    while (s[++i])
        printf("%s\n", s[i]);
}

void    ft_execve(void)
{
    char    *command;
    char    **command_all;
    int     fd[2];
    pid_t   pid;
    char    *path;
    int     path_n = 0;

	env_2D();
    command = g_glob.tok->data;
    command_all = make_tok2D();
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
            path = do_join(path, command_all[path_n]);
            // path = do_join(path, command);
            // printf_2d(command_all);
            printf("%s\n", path);
            if (!access(path, F_OK))
                execve(path, command_all, g_glob.env_ori);
            path = ft_strdup(g_glob.path[path_n]);
            path_n++;
        }
        exit(1);
    }
    // free_matrix(command_all); // 2개 이상의 문장이 들어가면 더블프리현상이 발생함.
    free(path);
    close(fd[1]);
    waitpid(pid, NULL, 0);
    close(fd[0]);
}