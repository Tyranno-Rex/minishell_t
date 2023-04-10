#include "../inc/minishell.h"

int main(int argc, char **argv, char **env)
{
    int hello = 0;
	hello = handler_builtins(argv, env);
	printf("\n1 success. 0 wrong: %d\n", hello);
}