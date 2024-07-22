#include "../../include/minishell.h"

void	ft_env(void)
{
	t_env *tmp_env;
	tmp_env = g_glob.env;
	g_glob.exit_stat = 0;
	while (tmp_env)
	{
		printf("%s=%s\n", tmp_env->key, tmp_env->val);
		tmp_env = tmp_env->next;
	}
}