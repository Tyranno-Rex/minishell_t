#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

#include "../libft/libft.h"





typedef struct s_export
{
    char        	*name;
    char        	*data;
    struct s_export	*next;
} t_export;


typedef struct s_data
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_data;



/*fd_return.c*/
t_data			*infile_set1(t_data *node, char **args, int *i);
t_data			*infile_set2(t_data *node, char **args, int *i);
int				get_fd(int oldfd, char *path, int flags[2]);



/*pipe.c*/
static t_data   *data_init(void);
static t_data   *set_cmd_content(t_data *node, char **argv[2], int *i);
int 			pipex(char **argv);
static char		**get_trimmed(char **args);

/*utils.c*/
static t_list	*stop_fill(t_list *cmds, char **args, char **contents);
static int		ft_count_len(char const *s1);
char			*ft_strtrim_all(char const *s1, int check_S, int check_L);
void			ft_free_matrix(char ***m);
int				ft_matrixlen(char **m);
char			**ft_dup_matrix(char **m);




// builtin.c
int     handler_builtins(char **data, char **env);

// pwd.c
int     ft_exec_pwd(char **data);
void    ft_pwd(void);

// exit.c
void	ft_exec_exit(char **data);

// echo.c
int     ft_exec_echo(char **declar);

// cd.c
int     ft_exec_cd(char **data);
void	ft_cd(char **command);

// env.c
void	ft_env(char **env);
int     ft_exec_env(char **data, char **env);