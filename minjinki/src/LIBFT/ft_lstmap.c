/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:41:31 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/18 14:29:42 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_token	*ft_free_node(t_token *head, void *tmp)
{
	ft_lstclear(&head);
	free(tmp);
	return (NULL);
}

t_token	*ft_lstmap(t_token *lst, void *(*f)(void *))
{
	t_token	*head;
	t_token	*cur;
	void	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = f(lst->data);
	head = ft_lstnew(tmp);
	if (!head)
		return (ft_free_node(head, tmp));
	cur = head;
	while (lst->next)
	{
		lst = lst->next;
		tmp = f(lst->data);
		cur->next = ft_lstnew(tmp);
		if (!cur->next)
			return (ft_free_node(head, tmp));
		cur = cur->next;
	}
	return (head);
}
