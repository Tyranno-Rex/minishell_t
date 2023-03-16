/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:48:54 by minjinki          #+#    #+#             */
/*   Updated: 2022/09/19 14:50:14 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*(unsigned char *)s != (unsigned char)c)
	{
		if (*(unsigned char *)s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}
