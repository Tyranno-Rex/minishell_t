#include "../inc/minishell.h"
char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*check_dots(char **args)
{
	size_t		i;
	char		*dir_param;
	static char	pwd[1024];

	dir_param = NULL;
	i = ft_strlen(args[1 + 1]);
	if (i == 1 && ft_strncmp(".", args[1 + 1], 1) == 0)
	{
		getcwd(pwd, 1024);
		return (pwd);
	}
	else if (i == 2 && ft_strncmp("..", args[1 + 1], 2) == 0)
		dir_param = "..";
	return (dir_param);
}

// cd 명령어가 몇개 있는 지 확인함.
int	ft_cd_len()
{
	int row;

	row = 0;
	while (g_glob.tok)
	{
		// 해당 부분 str이라고 정의함.
		if (g_glob.tok->type == 1)
			row++;
		g_glob.tok = g_glob.tok->next;
	}
	return (row);
}
static char	*validate_args(char **data)
{
	size_t	size;
	char	*dir_param;
	char	*tmp;

	size = ft_cd_len(data);
	// 인자가 2개만 진행되게 함
	if (size > 2)
		return (NULL);

	// 인자가 1개 -> cd 만 입력됐는 지 확인 (-> 이렇다면 홈 디렉으로 이동함) 
	// -> 이건 환경 변수 이야기 듣고 구현할 거임
	// else if (size == 1)
	// 	return (get_env_path("HOME", data));

	// . 이나 ..을 반환하는 결과
	tmp = check_dots();
	if (tmp)
	{
		dir_param = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
		ft_strcpy(dir_param, tmp);
	}
	else
		dir_param = tmp;
	// 만약에 cd와 cd .와 cd ..는 아닌 경우 ["절대 경로"]로 실행함.
	if (dir_param == NULL)
	{
		dir_param = ft_calloc(ft_strlen(data[2]) + 1, sizeof(char));
		ft_strcpy(dir_param, data[2]);
	}
	return (dir_param);
}

void	ft_cd()
{
	char	*new_directory;
	char	*oldpwd;
	char	pwd[5096];

	new_directory = validate_args(g_glob.cmd);
	printf("%s", new_directory);
	if (new_directory == NULL)
	{
		printf("minishell: cd: too many arguments");
		return ;
	}
	if (chdir(new_directory))
	{
		perror(new_directory);
		free(new_directory);
		return ;
	}
}
