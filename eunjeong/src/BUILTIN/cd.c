#include "../../include/minishell.h"

static char	*check_dots()
{
	t_glob		tmp;
	char		*dir_param = NULL;
	char		*dot;
	size_t		count = 0;
	static char	pwd[1024];

	tmp = g_glob;
	
	while(count < 2)
	{
		if (tmp.tok->type == 1 || tmp.tok->type == 34)
			count++;
		if (count > 1)
			dot = tmp.tok->data;
		tmp.tok = tmp.tok->next;
	}
	if (!strcmp(dot, "."))
	{
		getcwd(pwd, 1024);
		return (pwd);
	}
	else if (!strcmp(dot, ".."))
		dir_param = "..";
	else
		dir_param = dot;
	return (dir_param);
}

// cd 명령어가 몇개 있는 지 확인함.
int	ft_cd_len()
{
	int 	row;
	t_glob	tmp;

	row = 0;
	tmp = g_glob;
	while (tmp.tok)
	{
		// 해당 부분 str이라고 정의함.
		if (tmp.tok->type == 1 || tmp.tok->type == 34)
			row++;
		tmp.tok = tmp.tok->next;
	}
	return (row);
}

char	*get_env_path(char* target)
{
	t_glob tmp;
	
	tmp = g_glob;
	while (tmp.env)
	{
		if (!strncmp(tmp.env->key,target,4))
			return (tmp.env->val);
		tmp.env = tmp.env->next;
	}
	return (NULL);
}


char	*validate_args()
{
	int		size;
	char	*tmp = NULL;

	// printf("hello this is the cd test\n");
	size = ft_cd_len();
	// 인자가 1개 -> cd 만 입력됐는 지 확인 (-> 이렇다면 홈 디렉으로 이동함) 
	// -> 이건 환경 변수 이야기 듣고 구현할 거임
	if (size == 1)
		return (get_env_path("HOME"));
		// return (NULL);
	
	// . 이나 ..을 반환하는 결과
	// 인자가 2개만 진행되게 함.
	else if (size == 2)
		tmp = check_dots();
	if (tmp)
		return (tmp);
	else
		return (NULL);
}

void	ft_cd()
{
	char	*new_directory;
	// char	*oldpwd;

	new_directory = validate_args();
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
