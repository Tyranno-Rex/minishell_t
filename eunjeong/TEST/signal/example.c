#include <signal.h>
#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <termios.h>


void sig_handler(int signal)
{
    if (signal == SIGINT)
    {
        printf("\033[K"); //지워버리는 것을 원하지는 않았음.
        printf("nanoshell$ \n");
    }

    if (rl_on_new_line() == -1) // readline으로 설정한 문자열을 한 번 출력한다?
        exit(1);
    rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다.
    rl_redisplay();         // 프롬프트 커서가 움직이지 않게 해준다.
}

void setting_signal()
{
    signal(SIGINT, sig_handler); // CTRL + C
    signal(SIGQUIT, SIG_IGN);    // CTRL + /
                                 // signal(SIGTERM, sig_handler);
}

// setting_signal() 함수에서는 SIGINT(CTRL + C)와 SIGQUIT(CTRL + /) 시그널을 처리하도록 설정하며, SIGTERM 시그널은 처리하지 않습니다.

// main() 함수에서는 termios 구조체를 사용하여 입력된 문자열의 출력 방식을 설정합니다. ECHOCTL 플래그를 비활성화하여, 
// 커서가 위치한 곳의 문자열을 출력하지 않도록 합니다.

// while 루프에서는 readline() 함수를 사용하여 사용자로부터 입력을 받습니다. 입력된 문자열이 없는 경우(!str) 프로그램을 종료합니다. 
// 입력된 문자열이 비어있는 경우(*str == '\0')에는 free() 함수로 메모리를 해제합니다. 
// 그 외의 경우(else 절) 입력된 문자열을 add_history() 함수를 사용하여 히스토리에 추가하고, 
// 입력된 문자열을 출력한 뒤(printf("%s\n", str)) 메모리를 해제합니다(free(str)).

int main(int argc, char **argv, char **envp)
{
    char *str;
    struct termios term;
    
    // 현재 터미널의 속성을 가져와서 term 변수에 저장합니다.
    tcgetattr(STDIN_FILENO, &term);    
    // ECHOCTL 플래그를 비활성화하여, 커서가 위치한 곳의 문자열을 출력하지 않도록 합니다.
    term.c_lflag &= ~(ECHOCTL);
    // term 변수의 속성을 STDIN_FILENO에 적용합니다.
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    // 시그널 핸들러를 등록합니다.
    setting_signal();

    // 무한 루프를 실행합니다.
    while (1)
    {
        // "nanoshell$ " 프롬프트를 출력하고 사용자로부터 입력을 받습니다.
        str = readline("nanoshell$ ");
        // 입력된 문자열이 없는 경우(EOF) 프로그램을 종료합니다.
        if (!str)
        {
            printf("\033[1A");  // 커서를 이전 줄로 이동합니다.
            printf("\033[10C"); // 커서를 오른쪽으로 10칸 이동합니다.
            printf(" exit\n");  // " exit" 문자열을 출력합니다.
            exit(-1);           // 프로그램을 종료합니다.
        }
        // 입력된 문자열이 비어있는 경우에는 메모리를 해제합니다.
        else if (*str == '\0')
        {
            free(str);
        }
        // 그 외의 경우에는 입력된 문자열을 처리합니다.
        else
        {
            // 입력된 문자열을 히스토리에 추가합니다.
            add_history(str);
            // 입력된 문자열을 출력합니다.
            printf("%s\n", str);
            // 메모리를 해제합니다.
            free(str);
        }
    }

    // 프로그램을 종료합니다.
    return (0);
}