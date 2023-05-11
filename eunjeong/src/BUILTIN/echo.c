// #include "../../include/minishell.h"

// // cd 명령어가 몇개 있는 지 확인함.
// int	count_type_1()
// {
// 	int row;
// 	t_glob tmp; // 해당 부분 free 해야함

// 	tmp = g_glob;
// 	row = 0;
// 	while (tmp.tok)
// 	{
// 		// 해당 부분 str이라고 정의함.
// 		if (tmp.tok->type == 1)
// 			row++;
// 		tmp.tok = tmp.tok->next;
// 	}
// 	return (row);
// }

// int	ft_exec_echo(void)
// {
// 	bool	n_line;
// 	t_glob  tmp;
// 	int		i;

// 	n_line = true;
// 	i = count_type_1();
// 	tmp = g_glob;
// 	if (i > 1)
// 	{
// 		// echo는 넘겨야함
// 		tmp.tok = tmp.tok->next;
// 		while (tmp.tok->type != 1)
// 			tmp.tok = tmp.tok->next;
// 		if (tmp.tok->data && ft_strncmp(tmp.tok->data, "-n", 2) == 0)
// 		{
// 			n_line = false;
// 			tmp.tok = tmp.tok->next;
// 		}
// 		// 해당 내용 수정 해야함 echo 뒤의 값이 1이 맞는지 확인해야함
// 		while (tmp.tok->type != 1)
// 			tmp.tok = tmp.tok->next;
// 		while (tmp.tok)
// 		{
// 			printf("%s", tmp.tok->data);	
// 			tmp.tok = tmp.tok->next;
// 		}
// 	}
// 	if (n_line == true)
// 		printf("\n");
// 	return (0);
// }


#include "../../include/minishell.h"

// cd 명령어가 몇개 있는 지 확인함.
int   count_type_1()
{
   int row;
   t_glob tmp; // 해당 부분 free 해야함

   tmp = g_glob;
   row = 0;
   while (tmp.tok)
   {
      // 해당 부분 str이라고 정의함.
      if (tmp.tok->type == 1)
         row++;
      tmp.tok = tmp.tok->next;
   }
   return (row);
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

int   ft_exec_echo(void)
{
   bool   n_line;
   t_glob  tmp;
   int      i;

   n_line = true;
   i = count_type_1();
   tmp = g_glob;
   if (i > 1)
   {
      // echo는 넘겨야함
      tmp.tok = tmp.tok->next;
      while (tmp.tok->type != 1)
         tmp.tok = tmp.tok->next;
      if (tmp.tok->data && ft_strncmp(tmp.tok->data, "-n", 2) == 0
      && n_Test(tmp.tok->data))
      {
         n_line = false;
         tmp.tok = tmp.tok->next;
      }
      // 해당 내용 수정 해야함 echo 뒤의 값이 1이 맞는지 확인해야함
      while (tmp.tok->type != 1)
         tmp.tok = tmp.tok->next;
      while (tmp.tok)
      {
         printf("%s", tmp.tok->data);   
         tmp.tok = tmp.tok->next;
      }
   }
   if (n_line == true)
      printf("\n");
   return (0);
}
