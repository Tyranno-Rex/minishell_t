/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:02 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/11 16:43:35 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// 1개 만들때 오류 발생 왜 그런지 모르겠음
char **make_cmd_pipe(int pipe_num)
{
    int i = pipe_num;
    int cnt = -1;
    char *tmp;
    char **ret;
    char **ret_2;

	if (pipe_num == 1)
	{
    	ret = (char **)malloc(sizeof(char *) * (pipe_num + 1));
		ret[0] = ft_strdup(g_glob.cmd);
		return (ret);
	}
    ret = (char **)malloc(sizeof(char *) * (pipe_num + 1));
    ret_2 = ft_split(g_glob.cmd, '|');
    tmp = g_glob.cmd;

    while (++cnt < i)
    {
        ret[cnt] = ret_2[0];
        tmp += strlen(ret[cnt]) + 1;
        ret_2 = ft_split(tmp, '|');
    }

    ret[cnt] = ret_2[0];

    return ret;
}


// t_token *t_cmd_pipe(t_token **flow)
// {
//     t_token *ret_token = NULL;
//     t_token *flow_cp = *flow;
//     int token_len = 0;

//     while (flow_cp)
//     {
//         if (flow_cp->type == PIPE)
//             break;
//         token_len++;
//         flow_cp = flow_cp->next;
//     }
//     ret_token = (t_token *)calloc(token_len + 1, sizeof(t_token));

//     for (int i = 0; i < token_len; i++)
//     {
//         ret_token[i].data = ft_strdup((*flow)->data);
//         ret_token[i].type = (*flow)->type;
//         (*flow) = (*flow)->next;
//     }
// 	if (*flow)
//         *flow = (*flow)->next;
//     return ret_token;
// }
t_token *t_cmd_pipe(t_token **flow)
{
    t_token *ret_token = NULL;
    t_token *ret_current = NULL;
    t_token *flow_cp = *flow;

    while (flow_cp && flow_cp->type != PIPE)
    {
        t_token *new_token = (t_token *)malloc(sizeof(t_token));
        new_token->data = ft_strdup(flow_cp->data);
        new_token->type = flow_cp->type;
        new_token->next = NULL;

        if (ret_token == NULL)
        {
            ret_token = new_token;
            ret_current = new_token;
        }
        else
        {
            ret_current->next = new_token;
            ret_current = ret_current->next;
        }

        flow_cp = flow_cp->next;
    }

    if (flow_cp)
        *flow = flow_cp->next;
    else
        *flow = NULL;

    return ret_token;
}

int		pipe_len()
{
	t_glob tmp;
	int pipe_len;

	tmp = g_glob;
	pipe_len = 0;


	while (tmp.tok)
	{
		if (tmp.tok->type == PIPE)
			pipe_len++;
		tmp.tok = tmp.tok->next;
	}
	return (pipe_len);
}

void executor()
{
	int			pipe_num;
	char 		**cmd;
	t_token 	*flow = g_glob.tok;
	t_token		*block_token;
	int			*pip;

	pipe_num = pipe_len();
	cmd = (char **)malloc(sizeof(char *) * pipe_num + 1);
	// make_cmd(&cmd);

	// cmd = make_cmd_pipe(pipe_num);

	// int i = -1;
	// while (cmd[++i])
	// 	printf("pipe parsing test : %s\n", cmd[i]);

	pip = ft_calloc(4, pipe_num);

	while (pipe_num)
	{
		pipe(pip + (pipe_num - 1) * 2);
		pipe_num--;
	}
	pipe_num = pipe_len() + 1;
	block_token = t_cmd_pipe(&flow);
	// printf("data : %s\n", block_token->data );
	handler_builtins(block_token->data, block_token);
	
	// int i = -1;
	

	// while (pipe_num--)
	// {	
	// 	if (is_builtin(block_token->data) && (ft_strcmp(block_token->data, "exit") 
	// 		|| ft_strcmp(block_token->data, "export") || ft_strcmp(block_token->data, "unset")
	// 		|| ft_strcmp(block_token->data, "cd")))

	// 	pid_t	pid = fork();
	// 	// if (!pid){
	// 	// 	close_pipe_app();
	// 	// 	open_fd(); << fd , pipe 0, 1 << dup2();
	// 	// 	exe();
	// 	// 	close_pipe();
	// 	// 	close_fd();
	// 	// 	exit(0);
	// 	// }
	// 	// flow = flow->next;
	// }

}

////////////////////////////////////////////////////////////////////////////////////////
///////////////////////머리아파서 파일 나누는거 포기 main에서만 작업한다////////////////////
////////////////////////////////////////////////////////////////////////////////////////


void	print_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	ft_putstr_fd(ft_strrchr(pwd, '/') + 1, 1);
	free(pwd);
}


void Check_leak()
{
	system("leaks --list minishell");
}

void	minishell(void)
{
	setting_signal();
	init_rl_catch_signals();
	
	while (TRUE)
	{
		g_glob.cmd = readline(" minishell_$ ");
		if (!(g_glob.cmd))
			return ;
		if (!parse(g_glob.cmd))
		{
			free_cmd(g_glob.cmd);
			continue ;
		}
		env_2D();
		executor();
		free_cmd(g_glob.cmd);
	}
}

int	main(int ac, char **av, char **env)
{
	atexit(Check_leak);
	(void)av;
	if (ac != 1)
		exit_with_code("usage: ./minishell\n", 126);
	init_env(&env);
	minishell();
	free_all();
	return (SUCCESS);
}
