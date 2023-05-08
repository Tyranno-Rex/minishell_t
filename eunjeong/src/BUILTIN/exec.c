#include "../../include/minishell.h"







// static void *child_redir(int fd[2])
// {
//     t_glob tmp;

//     tmp = g_glob.root->pipe.
// }




// void *child_process(int fd[2])
// {
//     t_glob  *tmp;
//     int     l;

//     child_redir(fd);
// }






// void ft_execve(void)
// {
//     pid_t   pid;
//     int     fd[2];

//     pid = fork();
//     if (pid < 0)
//     {
//         close(fd[0]);
//         close(fd[1]);
//         printf("ERROR");
//     }
//     else if (!pid)
//         child_process(fd);
// }