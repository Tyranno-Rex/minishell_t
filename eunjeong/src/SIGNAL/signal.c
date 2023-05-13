#include "../../include/minishell.h"

void	init_rl_catch_signals(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
}

void sig_handler(int signal)
{
    if (signal == SIGINT)
    {
		printf("\n");
        printf("\033[K"); //지워버리는 것을 원하지는 않았음.
    }
    if (rl_on_new_line() == -1) // readline으로 설정한 문자열을 한 번 출력한다?
        exit(1);
    rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다.
    rl_redisplay();         // 프롬프트 커서가 움직이지 않게 해준다.
}

void setting_signal()
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}