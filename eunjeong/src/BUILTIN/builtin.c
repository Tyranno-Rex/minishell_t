#include "../../include/minishell.h"

int	is_builtin()
{
	int		count;
	t_glob	tmp;

	tmp = g_glob;
	
	if (!tmp.tok->data)
		return (0);
	count = ft_strlen(tmp.tok->data);
	if (!ft_strncmp(tmp.tok->data, "pwd", count) && count == 3)
		return (1);
	if (!ft_strncmp(tmp.tok->data, "env", count) && count == 3)
		return (1);
	if (!ft_strncmp(tmp.tok->data, "cd", count) && count == 2)
		return (1);
	if (!ft_strncmp(tmp.tok->data, "export", count) && count == 6)
		return (1);
	if (!ft_strncmp(tmp.tok->data, "unset", count) && count == 5)
		return (1);
	if (!ft_strncmp(tmp.tok->data, "echo", count) && count == 4)
		return (1);
	if (!ft_strncmp(tmp.tok->data, "exit", count) && count == 4)
		return (1);
	return (0);
}


// int	handler_builtins(char **data, char **env)
void	handler_builtins(void)
{
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
	// 	ft_exec_unset();
	if (!is_builtin())
		ft_exec_execve();
}

