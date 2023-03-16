#include "execute.h"

void ft_pwd_func()
{
    char *now_dir;
    now_dir = getcwd(NULL, 0);
    write(1, now_dir, strlen(now_dir)); // strlen -> ft_strlen 교체
    free(now_dir);
}

void ft_exit_func()
{
    printf("exit success!\n");
    exit(EXIT_SUCCESS);
    // free(); -> 이 부분은 추후에 내용이 첨가 되어야 함.
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


void ft_cd_func(char **argv, char **env)
{
    int ch;
    char *user_id;
    char *home_dir = ".\\home\\";

    if (!argv[2]) 
    {
        ch = chdir("/");
        user_id = ft_get_userid(env);
        char *new_dir = strjoin(home_dir, user_id);
        printf("new dir : %s\n", new_dir);
        if (new_dir) 
        {
            ch = chdir(new_dir);
            free(new_dir);
        }
    }
    else if (strncmp(argv[2], "..", 2))
    {
        char *now_dir;
        now_dir = getcwd(NULL, 0);
        printf("now_dir :  %s", now_dir);
    }
}


void ft_export_func(char **argv, t_data data)
{

    data.msg = 

}




int main(int argc, char **argv, char **env)
{
    int     i = 0;
    t_data  export_data;

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
        else if (strncmp(argv[1], "exit", 4) == 0)
        {
            setbuf(stdout, NULL);
            printf("exit test: "); // ft_printf
            ft_exit_func(argv);
        }
        else if (strncmp(argv[1], "cd", 2) == 0)
        {
            setbuf(stdout, NULL);
            ft_cd_func(argv, env);
            // printf("cd command execute :");
            // ft_pwd_func();
            // if( ch == 0 ) 
            //     printf("\nChange directory\n") ; // 디렉토리 이동 성공
            // else 
            //     printf("\nFailed change directory!\n") ; // 디렉토리 이동 실패 
        }
        else if (strncmp(argv[1], "export", 6) == 0)
        {
            ft_export_func(argv, export_data);
        }
    }
}