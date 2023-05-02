#include <unistd.h> 
#include <stdlib.h> 
#include "../inc/minishell.h" 

// minishell 구조체를 초기화
static t_data   *data_init(void)
{
    t_data  *mini;

    mini = malloc(sizeof(t_data));
    if (!mini) 
        return (NULL);
    mini->full_cmd = NULL; 
    mini->full_path = NULL; 
    mini->infile = STDIN_FILENO; 
    mini->outfile = STDOUT_FILENO; 
    return (mini); 
}


// 명령어의 인자 및 파일 입출력을 설정하는 함수
// argv[0] => argv의 문자열
// argv[1] => 파이프라인의 실행할 대상 -> 경로가 입력을 받아오면 좋을 것 같음
static t_data   *set_cmd_content(t_data *node, char **argv[2], int *i)
{
    // 명령어 인자 배열에서 아직 처리하지 않은 인자가 있는 경우
    if (argv[0][*i])
    {
        // 출력 리다이렉션(새 파일 생성)일 경우
        if (argv[0][*i][0] == '>') 
            node = outfile_set1(node, argv[1], i);
        // 출력 리다이렉션일 경우 (덮어 쓰기)
        else if (argv[0][*i][0] == '>' && argv[0][*i + 1] && argv[0][*i + 1][0] == '>')
            node = outfile_set2(node, argv[1], i);
        
		// 입력 리다이렉션(파일에서 입력)일 경우
        else if (argv[0][*i][0] == '<') 
            node = infile_set1(node, argv[1], i);
        // 입력 리다이렉션(Here Document)일 경우
        else if (argv[0][*i][0] == '<' && argv[0][*i + 1] && argv[0][*i + 1][0] == '<') 
            node = infile_set2(node, argv[1], i);
        
		// 입벽 리다이렉션(파이프)일 경우 
        else if (argv[0][*i][0] != '|') 
			node->full_cmd = ft_extend_matrix(node->full_cmd, argv[1][*i]);
		else
		{
			printf("wrong input\n");
			*i = -2;
		}
		return (node);
	}
	printf("wrong input\n");
	*i = -2;
	return (node);
}

// 문자열 앞뒤 공백 제거 함수
static char	**get_trimmed(char **args)
{
	char	**contents;
	char	*tmp;
	int		j;

	j = -1;
	// 주어진 문자열 배열 args를 복사한 새로운 배열 생성
	contents = ft_dup_matrix(args);
	// contents[j]가 NULL이 아닐 때까지
	while (contents && contents[++j])
	{
		// contents[j]의 앞뒤 공백 제거하여 tmp에 저장
		tmp = ft_strtrim_all(contents[j], 0, 0);
		// 이전 contents[j]에 할당된 메모리 해제
		free(contents[j]);
		// 앞뒤 공백 제거된 문자열 tmp를 contents[j]에 할당
		contents[j] = tmp;
	}
	// tmp가 NULL이 아닐 경우 tmp에 할당된 메모리 해제
	if (tmp)
		free(tmp);
	return (contents);
}


int pipex(char **argv)
{
    t_list	*cmds[2];
	char	**contents[2];

	cmds[0] = NULL; // 초기화
	contents[1] = get_trimmed(argv); // args 배열을 복사하여, 각 문자열의 앞뒤 공백을 제거한 contents[1] 배열 생성
	
    
    while (args[++i]) // args 배열의 모든 문자열을 탐색
	{
		cmds[1] = ft_lstlast(cmds[0]); // cmds[0] 리스트의 마지막 노드를 cmds[1]에 저장
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|'; // "|" 기호는 구분자이므로, 다음 인덱스로 이동
			ft_lstadd_back(&cmds[0], ft_lstnew(data_init())); // cmds[0] 리스트의 끝에 새로운 노드 추가
			cmds[1] = ft_lstlast(cmds[0]); // cmds[1]에 cmds[0] 리스트의 마지막 노드 저장
		}
		contents[0] = args; // contents[0] 배열에 args 배열 저장
		cmds[1]->content = set_cmd_content(cmds[1]->content, contents, &i); // cmds[1] 노드의 content 필드에 set_cmd_content() 함수 실행 결과 저장
		if (i < 0)
			return (stop_fill(cmds[0], args, contents[1])); // 에러가 발생하면, stop_fill() 함수 호출
		if (!args[i])
			break ;
	}
    return 0;
}

int main(int argc, char **argv, char **envp)
{
    int i = pipex(argv);
}