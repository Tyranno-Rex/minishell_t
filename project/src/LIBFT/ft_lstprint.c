/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:00:44 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/28 18:54:21 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstprint(t_token **lst)
{
	t_token	*cur;

	cur = *lst;
	printf("===================================\n\n");
	while (cur)
	{
		printf("type: %d\n", cur->type);
		printf("data: %s\n\n", cur->data);
		cur = cur->next;
	}
	printf("===================================\n");
}
