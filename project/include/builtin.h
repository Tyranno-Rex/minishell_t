#ifndef BUILTIN_H
# define BUILTIN_H

// builtin.c
void	handler_builtins(char *cmd, t_token *block);
int	    is_builtin(char *cmd);
char    **check_argv(void);

// builtin_exec.c
int	    ft_exec_pwd(void);

// pwd.c
void	ft_pwd(void);

// echo.c
int	    ft_echo(t_token *block);

// exit.c
void	ft_exec_exit(void);

// env.c
void    ft_env(void);
void    ft_exec_env(void);

// cd.c
void    ft_exec_cd(void);
void	ft_cd(t_token *block);

// export.c
void	ft_exec_export(void);
void    ft_export(t_token *block);

// exec.c
void	ft_exec_execve(void);
void    ft_execve(t_token *block);


// unset.c
void	ft_exec_unset(void);
void    ft_unset(t_token *block);

#endif