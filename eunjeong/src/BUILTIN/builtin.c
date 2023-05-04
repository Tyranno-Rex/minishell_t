#include "../../include/minishell.h"

// int	handler_builtins(char **data, char **env)
void	handler_builtins(void)
{
	// while (g_glob.tok)
	// {
	// 	printf("glob data : %s\n", g_glob.tok->data);
	// 	g_glob.tok = g_glob.tok->next;
	// }

	if (ft_strncmp(g_glob.cmd, "pwd", 3) == 0)
		ft_exec_pwd();
	if (ft_strncmp(g_glob.cmd, "exit", 4) == 0)
		ft_exec_exit();
	if (ft_strncmp(g_glob.cmd, "echo", 4) == 0)
		ft_exec_echo();
	if (ft_strncmp(g_glob.cmd, "env", 3) == 0)
		ft_exec_env();
	if (ft_strncmp(g_glob.cmd, "cd", 2) == 0)
		ft_exec_cd();
	if (ft_strncmp(g_glob.cmd, "export", 6) == 0)
		ft_exec_export();
	// if (ft_strncmp(g_glob.cmd, "unset", 5) == 0)
		// ft_exec_unset(data);
}