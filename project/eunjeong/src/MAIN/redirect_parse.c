#include "../../include/minishell.h"
void   add_token(t_token **lst, int type, char *data)
{
   t_token   *new;

   new = ft_lstnew(type, ft_strdup(data));
   ft_lstadd_back(lst, new);
}

t_token   *chk_start_is_redi(t_token **lst, t_token *cur)
{
   int      i;

   if (cur->type == LREDI || cur->type == HEREDOC || cur->type == RREDI || cur->type == RRREDI)   // 맨 처음에 리다이렉션
   {
      i = 2;
      while (i--)   // 리다이렉션 && 파일 변수 총 2번 반복
      {
         add_token(lst, cur->type, cur->data);   // 노드 정보 복사 붙여넣기
         cur = cur->next;
         while (cur && cur->type == SPACES)
            cur = cur->next;   // 다음 노드로 옮기기
         add_token(lst, SPACES, " ");
      }
   }
   return (cur);
}

void   copy_redi(t_token **lst, t_token *cur)
{
   while (cur)
   {
      add_token(lst, cur->type, cur->data);      // 노드 정보 복사 붙여넣기
      cur = cur->next;
      while (cur && cur->type == SPACES)
         cur = cur->next;
      if (cur->next) // 다음 노드 없으면 공백 추가하지 않도록
         add_token(lst, SPACES, " ");
   }
}

t_token   *get_till_redi(t_token **flow)
{
   t_token   *cur;
   t_token   *new_list;
   t_token   *new_tok;

   cur = *flow;
   new_list = NULL;
   cur = chk_start_is_redi(&new_list, cur);   // 명령어 맨 처음이 리다이렉션인지 확인
   new_tok = ft_lstnew(cur->type, "");
   ft_lstadd_back(&new_list, new_tok);
   if (cur && (cur->type != LREDI || cur->type != HEREDOC || cur->type != RREDI || cur->type != RRREDI))
   {
      while (cur && (cur->type != LREDI || cur->type != HEREDOC || cur->type != RREDI || cur->type != RRREDI))
      {
         new_tok->data = do_join(new_tok->data, cur->data);
         cur = cur->next;
      }
   }
   copy_redi(&new_list, cur);   // 리다이렉션은 개별적으로 넣기
   return (new_list);
}