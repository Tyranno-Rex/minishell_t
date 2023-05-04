/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjeong <eunjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:53:26 by eunjeong          #+#    #+#             */
/*   Updated: 2022/07/25 19:11:20 by eunjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t cnt, size_t size)
{
	unsigned char	*tmp;

	tmp = malloc(size * cnt);
	if (!(tmp))
		return (NULL);
	ft_bzero(tmp, size * cnt);
	return (tmp);
}
