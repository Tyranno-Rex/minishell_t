#include "../../include/minishell.h"

void	ft_exec_exit(void)
{
	bool check;

	// free_all()에러 발생
	check = free_all();
	if (check)
		exit(SUCCESS);
	exit(SUCCESS);
}
