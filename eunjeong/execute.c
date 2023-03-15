#include "execute.h"


void ft_pwd_func()
{
    char *now_dir;
    now_dir = getcwd(NULL, 0);
    write(1, now_dir, strlen(now_dir)); // strlen -> ft_strlen 교체
    free(now_dir);
}





// -n 옵션은 메세지 이전에 나올때만 실행됨 때문에 -n옵션은 처음에만 확인하면 됨
void ft_echo_func(char **argv) // 이건 -> 연결리스트와 같은 데이터로 받는게 좋을듯 -> 안에서 구현하는 것을 지향
{
    int i;
    int flag;

    i = 1;
    flag = 1;
    while (argv && argv[++i])
    {
        if (i == 2 && strncmp(argv[i], "-n", 2) == 0) // ft_strncmp
            flag = 0;
		else
		{
            write(1, argv[i], strlen(argv[i])); // ft_strlen
			if (argv[i + 1])
                write(1, " ", 1);
		}
	}
    write(1, "\n", flag);
}

int main(int argc, char **argv)
{
    if (argc >= 2)
    {
        if (strncmp(argv[1], "pwd", 3) == 0)
        {
            setbuf(stdout, NULL);
            printf("pwd test: \n"); // ft_printf
            ft_pwd_func();
            write(1, "\n", 1);
        }
        else if (strncmp(argv[1], "echo", 4) == 0)
        {
            setbuf(stdout, NULL);
            printf("echo test: \n"); // ft_printf
            ft_echo_func(argv);
        }
    }
}