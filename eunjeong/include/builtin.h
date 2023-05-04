#ifndef BUILTIN_H
# define BUILTIN_H

// builtin.c
void	handler_builtins(void);

// builtin_exec.c
int	    ft_exec_pwd(void);

// pwd.c
void	ft_pwd(void);

// echo.c
int	    ft_exec_echo(void);

// exit.c
void	ft_exec_exit(void);

// env.c
void    ft_env(void);
void    ft_exec_env(void);


// cd.c
int     ft_exec_cd(void);
void	ft_cd(void);

#endif