#include "../inc/minishell.h"

// heredoc로 입력된 문자열을 저장하는 함수
char *get_here_str(char *str[2], size_t len, char *limit, char *warn)
{
    char *temp;

    // g_status가 130이 아니면서 str[0]이 NULL이거나 limit과 str[0]의 값이 일치하지 않을 때까지 반복
    while ((!str[0] || ft_strncmp(str[0], limit, len) \
        || ft_strlen(limit) != len))
    {
        // temp에 이전에 할당된 문자열 저장
        temp = str[1];

        // str[0]에 입력된 문자열 추가
        str[1] = ft_strjoin(str[1], str[0]);

        // 이전 문자열과 str[0]을 메모리에서 해제
        free(temp);
        free(str[0]);

        // 새로 입력된 문자열을 str[0]에 저장
        str[0] = readline("> ");

        // str[0]이 NULL이면 ERROR 출력 후 루프 종료
        if (!str[0])
        {
            printf("ERROR\n");
            break;
        }

        // str[0]에 개행 문자 추가
        temp = str[0];
        str[0] = ft_strjoin(str[0], "\n");
        free(temp);

        // 문자열 길이에서 1을 빼고 len에 저장
        len = ft_strlen(str[0]) - 1;
    }

    // str[0] 메모리 해제 후 str[1] 반환
    free(str[0]);
    return (str[1]);
}

// heredoc을 실행하는 함수
int get_here_doc(char *path)
{
    char *str[2];
    int fd[2];

    // 파이프 생성
    if (pipe(fd) == -1)
    {
        mini_perror(PIPERR, NULL, 1);
        return (-1);
    }

    // heredoc으로 입력된 문자열을 str[1]에 저장
    str[1] = get_here_str(str, 0, aux[0]);

    // 파이프에 str[1]의 내용을 쓰기
    write(fd[WRITE_END], str[1], ft_strlen(str[1]));

    // 메모리에서 str[1] 해제
    free(str[1]);

    // 파이프의 쓰기 파일 디스크립터 닫기
    close(fd[WRITE_END]);

    // 파이프의 읽기 파일 디스크립터 반환
    return (fd[READ_END]);
}