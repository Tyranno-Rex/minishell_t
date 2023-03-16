#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]) {
    char *user = NULL;
    for (int i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], "USER=", 5) == 0) {
            user = env[i] + 5;
            break;
        }
    }
    if (user == NULL) {
        printf("Error: USER environment variable is not set\n");
        return 1;
    }
    printf("User ID: %s\n", user);
    return 0;
}