#include "../inc/minishell.h"

int	handler_builtins(char **data)
{
	if (ft_strncmp(data[1], "pwd", 3) == 0)
		ft_exec_pwd(data);
	if (ft_strncmp(data[1], "exit", 4) == 0)
		ft_exec_exit(data);
	if (ft_strncmp(data[1], "echo", 4) == 0)
		ft_exec_echo(data);
	if (ft_strncmp(data[1], "cd", 2) == 0)
		ft_exec_cd(data);
	return (1);
	// if (ft_strcmp(data[1],"export") == 0)
	// 	ft_export(data);
	// if (ft_strcmp(data[1], "unset") == 0)
	// 	ft_unset(data);
	// if (ft_strcmp(data[1], "env") == 0)
	// 	ft_env(data);
}


int main(int argc, char **argv)
{
    int hello = 0;
	hello = handler_builtins(argv);
	printf("\n1 success. 0 wrong: %d\n", hello);
}