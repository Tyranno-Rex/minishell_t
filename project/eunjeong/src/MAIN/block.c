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