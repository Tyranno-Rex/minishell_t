
typedef struct s_data
{
    char *env;

} t_data;

void	unset(char **args)
{
	int		i;
	int		j;
	char	*var;

	i = -1;
	var = args[0];
	if (!var)
		return ;
	while (g_data.env[++i])
	{
		j = 0;
		while (g_data.env[i][j] == var[j] && var[j] != '=' && var[j])
			j++;
		if ((g_data.env[i][j] == '=' || !g_data.env[i][j]) && var[j] == '\0')
		{
			free(g_data.env[i]);
			while (g_data.env[i])
			{
				g_data.env[i] = g_data.env[i + 1];
				i++;
			}
			break ;
		}
	}
	unset(args + 1);
}

static int	check_args(char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[0]) && args[0] != '_')
		return (0);
	while (args[i] && args[i] != '=')
	{
		if ((!ft_isalnum(args[i]) && args[i] != '+') || \
		(args[i] == '+' && args[i + 1] != '='))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(char **args)
{
	int	i;
	int	j;
    t_data data;
	j = 0;
	if (!args[1])
		return (sorted_env());
	while (args[++j])
	{
		if (!check_args(args[j]))
			break ;
		else if (!existing_var(args[j]))
		{
			i = 0;
			while (data.env && data.env[i])
				i++;
			data.env = realloc_envv(i + 1);
			data.env[i] = getvar(args[j]);
			data.env[i + 1] = NULL;
		}
	}
}
