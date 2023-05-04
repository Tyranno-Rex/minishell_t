#include "../../include/minishell.h"

// int	handler_builtins(char **data, char **env)
void	handler_builtins(void)
{
	while (g_glob.tok)
	{
		printf("glob data : %s\n", g_glob.tok->data);
		g_glob.tok = g_glob.tok->next;
	}
	
	
	
	if (ft_strncmp(g_glob.cmd, "pwd", 3) == 0)
		ft_exec_pwd();
		// printf("pwd command is runnig\n");
	if (ft_strncmp(g_glob.cmd, "exit", 4) == 0)
		printf("exit command is runnig\n");
		// ft_exec_exit(data);
	if (ft_strncmp(g_glob.cmd, "echo", 4) == 0)
		printf("echo command is runnig\n");
		// ft_exec_echo(data);
	if (ft_strncmp(g_glob.cmd, "cd", 2) == 0)
		printf("cd command is runnig\n");
		// ft_exec_cd(data);
	if (ft_strncmp(g_glob.cmd, "env", 3) == 0)
		printf("env command is runnig\n");
		// ft_exec_env(data, env);
	// if (ft_strncmp(g_glob.cmd, "clear", 5))
	// 	execue(g_glob.cmd);
	// if (ft_strncmp(g_glob.cmd, "export", 6) == 0)
		// ft_exec_export(data);
	// if (ft_strncmp(g_glob.cmd, "unset", 5) == 0)
		// ft_exec_unset(data);
}