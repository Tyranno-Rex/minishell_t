#include <stdio.h>
#include <unistd.h>

int main(int argc, char **av,  char **envp)
{
    char *path[9];
    char *argv[] = {"clear", "ls", NULL};
    int i = 0;
    
    path[0] = "/Users/eunjeong/.brew/bin";
    path[1] = "/Users/eunjeong/.brew/bin";
    path[2] = "/Users/eunjeong/.brew/bin";
    path[3] = "/usr/local/bin";
    path[4] = "/usr/bin";
    path[5] = "/bin";
    path[6] = "/usr/sbin";
    path[7] = "/sbin";
    path[8] = "/usr/local/munki";
    
    while(path[i])
    {
        if (execve(path[i], argv, envp) == -1)
        {
            printf("%s ", path[i]);
            printf("%d\n", i);
        }
        
        i++;
    }
}