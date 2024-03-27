/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:41:31 by minjinki          #+#    #+#             */
/*   Updated: 2022/07/20 14:03:04 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_free_node(t_list *head, void *tmp, void (*del)(void *))
{
	ft_lstclear(&head, del);
	del(tmp);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*cur;
	void	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = f(lst->content);
	head = ft_lstnew(tmp);
	if (!head)
		return (ft_free_node(head, tmp, del));
	cur = head;
	while (lst->next)
	{
		lst = lst->next;
		tmp = f(lst->content);
		cur->next = ft_lstnew(tmp);
		if (!cur->next)
			return (ft_free_node(head, tmp, del));
		cur = cur->next;
	}
	return (head);
}
