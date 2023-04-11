#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include "../libft/libft.h"


typedef struct s_export
{
    char        *name;
    char        *data;
    t_export    *next;
} t_export;



// builtin.c
int     handler_builtins(char **data, char **env);

// pwd.c
int     ft_exec_pwd(char **data);
void    ft_pwd(void);

// exit.c
void	ft_exec_exit(char **data);

// echo.c
int     ft_exec_echo(char **declar);

// cd.c
int     ft_exec_cd(char **data);
void	ft_cd(char **command);

// env.c
void	ft_env(char **env);
int     ft_exec_env(char **data, char **env);