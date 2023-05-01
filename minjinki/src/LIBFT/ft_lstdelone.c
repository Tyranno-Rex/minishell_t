/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:15:38 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/01 15:41:07 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_token *lst)
{
	if (!lst)
		return ;
	free(lst->data);
	lst->data = NULL;
	free(lst);
	lst = NULL;
}
