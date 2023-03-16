#include "execute.h"

char *strjoin(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (!result) return NULL;
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}



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


int main(int argc, char **argv, char **env)
{
    char    *user = NULL;
    int     i = 0;

    /*유저 조회*/
    while (env[i++])
    {
        if (strncmp(env[i], "USER=", 5) == 0) 
        {
            user = env[i] + 5;
            break;
        }
    }
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
        else if (strncmp(argv[1], "cd", 2) == 0)
        {
            setbuf(stdout, NULL);
            int ch;
            char *home_dir = ".\\home\\";
            if (!argv[2]) {
                ch = chdir("/");
                char *new_dir = strjoin(home_dir, user);
                printf("new dir : %s\n", new_dir);
                if (new_dir) {
                    ch = chdir(new_dir);
                    free(new_dir);
                }
            }
            else
                ch = chdir("C:\\Coding\\42seoul\\minishell_project\\");
            printf("cd command execute :");
            ft_pwd_func();
            if( ch == 0 ) 
                printf("\nChange directory\n") ; // 디렉토리 이동 성공
            else 
                printf("\nFailed change directory!\n") ; // 디렉토리 이동 실패 
        }
    }
}