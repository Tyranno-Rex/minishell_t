#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	int		count;
	t_glob	tmp;

	tmp = g_glob;
	
	if (!cmd)
		return (0);
	count = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "pwd", count) && count == 3)
		return (1);
	if (!ft_strncmp(cmd, "env", count) && count == 3)
		return (1);
	if (!ft_strncmp(cmd, "cd", count) && count == 2)
		return (1);
	if (!ft_strncmp(cmd, "export", count) && count == 6)
		return (1);
	if (!ft_strncmp(cmd, "unset", count) && count == 5)
		return (1);
	if (!ft_strncmp(cmd, "echo", count) && count == 4)
		return (1);
	if (!ft_strncmp(cmd, "exit", count) && count == 4)
		return (1);
	return (0);
}


// int	handler_builtins(char **data, char **env)
void	handler_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		ft_exec_pwd();
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		ft_exec_exit();
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		ft_exec_echo();
	else if (ft_strncmp(cmd, "env", 3) == 0)
		ft_exec_env();
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_exec_cd();
	else if (ft_strncmp(cmd, "export", 6) == 0)
		ft_exec_export();
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		ft_exec_unset();
	else if (!is_builtin(cmd))
		ft_exec_execve();
}

