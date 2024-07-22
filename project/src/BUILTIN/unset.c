#include "../../include/minishell.h"

void	ft_unset(t_token *block)
{
	t_env	*node;
	t_env	*pre;
	t_token	*tok;

	tok = block->next;
	while (tok)
	{
		pre = NULL;
		node = g_glob.env;
		while (node)
		{
			if (ft_strcmp(tok->data, node->key) == 0)
			{
				printf("tok->data: %s\n", tok->data);
				env_remove(pre, node);
				break ;
			}
			pre = node;
			node = node->next;
		}
		tok = tok->next;
	}
}