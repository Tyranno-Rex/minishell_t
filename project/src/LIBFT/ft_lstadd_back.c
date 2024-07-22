/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:13:18 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/28 17:11:48 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_lstadd_back(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return (FALSE);
	else if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
	return (TRUE);
}
