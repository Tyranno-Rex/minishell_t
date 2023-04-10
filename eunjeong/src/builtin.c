#include "../inc/minishell.h"

int	handler_builtins(char **data, char **env)
{
	if (ft_strncmp(data[1], "pwd", 3) == 0)
		ft_exec_pwd(data);
	if (ft_strncmp(data[1], "exit", 4) == 0)
		ft_exec_exit(data);
	if (ft_strncmp(data[1], "echo", 4) == 0)
		ft_exec_echo(data);
	if (ft_strncmp(data[1], "cd", 2) == 0)
		ft_exec_cd(data);
	if (ft_strncmp(data[1], "env", 3) == 0)
		ft_exec_env(data, env);
	return (1);
	// if (ft_strncmp(data[1], "export", 6) == 0)
	// 	ft_exec_export(data);
	// if (ft_strncmp(data[1], "unset", 5) == 0)
	// 	ft_exec_unset(data);
}