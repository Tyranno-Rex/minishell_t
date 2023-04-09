/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjeong <eunjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 19:35:15 by eunjeong          #+#    #+#             */
/*   Updated: 2022/08/18 16:42:25 by eunjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*target;
	t_list		*result;

	result = NULL;
	while (lst)
	{
		target = ft_lstnew(f(lst->content));
		if (!target)
		{
			ft_lstclear(&result, del);
			return ((void *)(0));
		}
		ft_lstadd_back(&result, target);
		lst = lst->next;
	}
	target = NULL;
	return (result);
}
