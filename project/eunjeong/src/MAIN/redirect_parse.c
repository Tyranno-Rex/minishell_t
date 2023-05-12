#include "../../include/minishell.h"

t_token   *chk_start_is_redi(t_token **lst, t_token *cur)
{
   int      i;
   char   *s;
   t_token   *new;

   if (cur->type == LREDI || cur->type == HEREDOC || cur->type == RREDI || cur->type == RRREDI)   // 맨 처음에 리다이렉션
   {
      i = 2;
      while (i--)   // 리다이렉션 && 파일 변수 총 2번 반복
      {
         s = ft_strdup(cur->data);
         new = ft_lstnew(cur->type, s);
         ft_lstadd_back(lst, new);   // 노드 정보 복사 붙여넣기
         cur = cur->next;
         while (cur && cur->type == SPACES)
            cur = cur->next;   // 다음 노드로 옮기기
         // 공백 추가
         //s = ft_strdup(" ");
         //new = ft_lstnew(SPACES, s);
         //ft_lstadd_back(lst, new);
      }
   }
   return (cur);
}

void   copy_redi(t_token **lst, t_token *cur)
{
   char   *s;
   t_token   *new;

   while (cur)
   {
      s = ft_strdup(cur->data);
      new = ft_lstnew(cur->type, s);
      ft_lstadd_back(lst, new);   // 노드 정보 복사 붙여넣기
      cur = cur->next;
      while (cur && cur->type == SPACES)
         cur = cur->next;
      // 공백 추가
      //if (cur->next) // 다음 노드 없으면 공백 추가하지 않도록
      //{
      //   s = ft_strdup(" ");
      //   new = ft_lstnew(SPACES, s);
      //   ft_lstadd_back(lst, new);
      //}
   }
}

t_token   *get_till_redi(t_token **flow)
{
   char   *s;
   t_token   *cur;
   t_token   *new_list;
   t_token   *new_tok;

   cur = *flow;
   new_list = NULL;
   cur = chk_start_is_redi(&new_list, cur);   // 명령어 맨 처음이 리다이렉션인지 확인
   s = ft_strdup("");
   if (cur && (cur->type != LREDI || cur->type != HEREDOC || cur->type != RREDI || cur->type != RRREDI))
   {
      while (cur && (cur->type != LREDI || cur->type != HEREDOC || cur->type != RREDI || cur->type != RRREDI))
      {
         s = do_join(s, cur->data);
         new_tok = ft_lstnew(cur->type, s);
         ft_lstadd_back(&new_list, new_tok);
         cur = cur->next;
      }
   }
   else
      free(s);   // 바로 리다이렉션이 다시 나옴 || 뒤에 토큰이 더 없음 > s 사용하지 않음
   copy_redi(&new_list, cur);   // 리다이렉션은 개별적으로 넣기
   return (new_list);
}