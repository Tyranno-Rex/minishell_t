#include "../../include/minishell.h"

// cd 명령어가 몇개 있는 지 확인함.
// int   count_type_1(t_token block)
// {
//    	int 	row;
//    	t_token *tmp = NULL;

//    	*tmp = block;
//    	row = 0;
//    	while (tmp)
//    	{
//       	// 해당 부분 str이라고 정의함.
//       	if (tmp->type != SPACES)
//          	row++;
//       	tmp = tmp->next;
//    	}
//    	return (row);
// }

int count_type_1(t_token *block)
{
    int row = 0;
    t_token *tmp = block;

    while (tmp)
    {
        // 해당 부분 str이라고 정의함.
        if (tmp->type != SPACES)
            row++;
        tmp = tmp->next;
    }

    return row;
}


int n_Test(char *msg)
{
   	int i;

   	i = 1;
   	if (msg[0] != '-' && msg[1] != 'n')
     	return (0);
   	while (msg[++i])
   	{
      	if (msg[i] != 'n')
         	return (0);
   	}
   	return (1);
}

int   ft_echo(t_token *block)
{
   	t_token  	*tmp;
	bool   		n_line;
   	int      	i;

    tmp = NULL;
   	n_line = true;
   	i = count_type_1(block);
   	tmp = block;
   	if (i > 1)
   	{
      // echo는 넘겨야함
    	tmp = tmp->next;
    	while (tmp->type == SPACES)
        	tmp = tmp->next;
      	if (tmp->data && ft_strncmp(tmp->data, "-n", 2) == 0
      		&& n_Test(tmp->data))
      	{
        	n_line = false;
    		tmp = tmp->next;
      	}
    	// 해당 내용 수정 해야함 echo 뒤의 값이 1이 맞는지 확인해야함
    	while (tmp->type == SPACES)
        	tmp = tmp->next;
		while (tmp)
      	{
        	printf("%s", tmp->data);   
        	tmp = tmp->next;
      	}
	}
	if (n_line == true)
		printf("\n");
   	return (0);
}
