#include "../../include/minishell.h"

int check_excute_one()
{
	t_glob tmp = g_glob;
	int		i;

	i = 2;
	while (tmp.tok)
	{
		// printf("%s\n", tmp.tok->data);
		if (tmp.tok->type != STR && tmp.tok->type != SPACES)
			return (0);
		if (is_builtin(tmp.tok->data))
			i = 1;
		tmp.tok = tmp.tok->next;
	}
	return (i);
}

int	check_single_excute()
{
	char	**cmd_argv;

	cmd_argv = make_tok2D(g_glob.tok);
	if(check_excute_one() == 1)
	{
		handler_builtins(g_glob.tok->data, g_glob.tok);
		return (1);
	}
	else if(check_excute_one() == 2)
	{
		ft_execve(g_glob.tok);
		return (1);
	}
	return (0);
}