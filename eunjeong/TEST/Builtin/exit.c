#include "../inc/minishell.h"

void	ft_exec_exit(char **data)
{
	if (data[2] != NULL)
	{
		printf("exit sucess!\n");
		exit(ft_atoi(data[2]));
	}
	else
	{
		printf("exit sucess!\n");
		exit(EXIT_SUCCESS);
	}
}
