#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include "../libft/libft.h"


// static char	*validate_args(char **data);
// int	        ft_cd_len(char **tab);
// static char *check_dots(char **args);
// void	    ft_setenv(t_builtin_vars *builtins, char *name, char *value);
// static void change_value(t_node *current, char **splitted, char *value);
// char	    *get_env_path(char *path, t_builtin_vars *builtin);
// void	    ft_setenv(t_builtin_vars *builtins, char *name, char *value);


// builtin.c
int	handler_builtins(char **data);

// pwd.c
int     ft_exec_pwd(char **data);
void    ft_pwd(void);

// exit.c
void	ft_exec_exit(char **data);

// echo.c
int     ft_exec_echo(char **declar);

// ft_cd.c
int     ft_exec_cd(char **data);
void	ft_cd(char **command);