#include "../../include/minishell.h"

// int	handler_builtins(char **data, char **env)
int	handler_builtins()
{
	printf("glob data : %s\n", g_glob.cmd);
	if (ft_strncmp(g_glob.cmd, "pwd", 3) == 0)
		printf("pwd command is runnig\n");
		// ft_exec_pwd(data);
	if (ft_strncmp(g_glob.cmd, "exit", 4) == 0)
		printf("pwd command is runnig\n");
		// ft_exec_exit(data);
	if (ft_strncmp(g_glob.cmd, "echo", 4) == 0)
		printf("pwd command is runnig\n");
		// ft_exec_echo(data);
	if (ft_strncmp(g_glob.cmd, "cd", 2) == 0)
		printf("pwd command is runnig\n");
		// ft_exec_cd(data);
	if (ft_strncmp(g_glob.cmd, "env", 3) == 0)
		printf("pwd command is runnig\n");
		// ft_exec_env(data, env);
	if (ft_strncmp(g_glob.cmd, "clear", 5))
		execue(g_glob.cmd);
	return (1);
	// if (ft_strncmp(g_glob.cmd, "export", 6) == 0)
		// ft_exec_export(data);
	// if (ft_strncmp(g_glob.cmd, "unset", 5) == 0)
		// ft_exec_unset(data);
}