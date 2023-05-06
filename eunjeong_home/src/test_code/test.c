int i = 0;
char **tmp_path;
tmp_path = g_glob.path;
while (tmp_path[i])
    printf("path: %s\n", tmp_path[i++]);