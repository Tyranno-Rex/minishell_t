#include "../inc/minishell.h"

static t_list	*stop_fill(t_list *cmds, char **args, char **contents)
{
	ft_lstclear(&cmds, free_content); 
	ft_free_matrix(&contents); 
	ft_free_matrix(&args); // args 배열 해제
	return (NULL);
}

static int	ft_count_len(char const *s1)
{
	int	count;
	int	i;
	int	check_L;
	int	check_S;

	i = 0;
	count = 0;
	check_L = 0;
	check_S = 0;
	while (s1 && s1[i])
	{
		check_S = (check_S + (!check_L && s1[i] == '\'')) % 2;
		check_L = (check_L + (!check_S && s1[i] == '\"')) % 2;
		if ((s1[i] == '\"' && !check_S) || (s1[i] == '\'' && !check_L))
			count++;
		i++;
	}
	if (check_S || check_L)
		return (-1);
	return (count);
}

char	*ft_strtrim_all(char const *s1, int check_S, int check_L)
{
	int		count;
	int		i[2];
	char	*trimmed;

	i[1] = -1;
	i[0] = 0;
	count = ft_count_len(s1);
	if (!s1 || count == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(s1) - count + 1));
	if (!trimmed)
		return (NULL);
	while (s1[i[0]])
	{
		check_S = (check_S + (!check_L && s1[i[0]] == '\'')) % 2;
		check_L = (check_L + (!check_S && s1[i[0]] == '\"')) % 2;
		if ((s1[i[0]] != '\"' || check_S) && (s1[i[0]] != '\'' || check_L) && ++i[1] >= 0)
			trimmed[i[1]] = s1[i[0]];
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}

// m에 할당된 메모리 해제 함수
void	ft_free_matrix(char ***m)
{
	int	i;

	i = 0;
	// m이 NULL이 아니고, m[0]이 NULL이 아니며, m[0][i]가 NULL이 아닐 때까지
	while (m && m[0] && m[0][i])
	{
		// m[0][i]에 할당된 메모리 해제
		free(m[0][i]);
		i++;
	}
	// m이 NULL이 아닐 때
	if (m)
	{
		// m[0]에 할당된 메모리 해제
		free(m[0]);
		// m이 가리키는 포인터를 NULL로 설정
		*m = NULL;
	}
}

// 행렬의 행의 길이(크기) 계산 함수
int	ft_matrixlen(char **m)
{
	int	i;

	i = 0;
	// m이 NULL이 아니고, m[i]가 NULL이 아닐 때까지
	while (m && m[i])
		i++;
	return (i);
}

// 행렬 복사 함수
char	**ft_dup_matrix(char **m)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	// 행렬의 행의 길이 계산
	n_rows = ft_matrixlen(m);
	// 행렬 복사를 저장할 out 배열 동적 메모리 할당
	out = malloc(sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	// 각각의 행 복사
	while (m[i])
	{
		// m[i]의 문자열 복사하여 out[i]에 할당
		out[i] = ft_strdup(m[i]);
		// out[i]가 NULL인 경우
		if (!out[i])
		{
			// 할당된 메모리 해제
			ft_free_matrix(&out);
			// NULL 반환
			return (NULL);
		}
		i++;
	}
	// out 배열의 마지막 인덱스에 NULL 할당
	out[i] = NULL;
	return (out);
}