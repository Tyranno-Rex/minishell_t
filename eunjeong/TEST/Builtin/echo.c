#include "../inc/minishell.h"

void	ft_print_export(char **argv)
{
	return ;
}


int	count_declar(char **argv)
{
	int	size;

	size = 0;
	while (argv[size])
		size++;
	return (size);
}

int	ft_exec_echo(char **argv)
{
	bool	n_line;
	int		i;

	i = 2;
	n_line = true;
	if (count_declar(argv) > 1)
	{
		while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
		{
			n_line = false;
			i++;
		}
		while (argv[i])
		{
			if (argv[i] == "$")
				ft_print_export(argv);
			ft_putstr_fd(argv[i], 1);
			if (argv[i][0] != '\0' && argv[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (n_line == true)
		write(1, "\n", 1);
	return (0);
}
