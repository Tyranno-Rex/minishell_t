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


char *ft_get_userid(char **env)
{
    int     i = 0;
    char    *user = NULL;
    /*유저 조회*/
    while (env[i++])
    {
        if (strncmp(env[i], "USER=", 5) == 0) 
        {
            user = env[i] + 5;
            break;
        }
    }
    return (user);
}