/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjeong <eunjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:12:24 by marvin            #+#    #+#             */
/*   Updated: 2022/07/25 16:55:05 by eunjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;

	if (dst == src || n == 0)
		return (dst);
	if (dst < src)
	{
		dest = (unsigned char *)dst;
		source = (unsigned char *)src;
		while (n--)
			*dest++ = *source++;
	}
	else
	{
		dest = (unsigned char *)dst + (n - 1);
		source = (unsigned char *)src + (n - 1);
		while (n--)
			*dest-- = *source--;
	}
	return (dst);
}
