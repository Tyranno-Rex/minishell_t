#include "../../include/minishell.h"


void    env_2D(void)
{
    t_env   *tmp;
	int		cnt;
    char    *key;
    char    *val;
	// char 	**new_env;

    tmp = g_glob.env;
	cnt = 0;
	free_matrix(g_glob.env_ori);
	
	while (tmp)
	{
		tmp = tmp->next;
		cnt++;
	}
	
	g_glob.env_ori = ft_calloc(++cnt, sizeof(char *));
    
	tmp =  g_glob.env;
	cnt = -1;
	
	while (tmp)
    {
        key = ft_strdup(tmp->key);
		g_glob.env_ori[++cnt] = do_join(key, "=");
        val = ft_strdup(tmp->val);
		g_glob.env_ori[cnt] = do_join(g_glob.env_ori[cnt] , val);
        free(val);
        val = NULL;
		tmp = tmp->next; 
    } 
}