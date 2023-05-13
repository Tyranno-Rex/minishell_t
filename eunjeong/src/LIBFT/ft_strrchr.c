/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:36:11 by minjinki          #+#    #+#             */
/*   Updated: 2022/07/20 15:26:01 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			len;
	unsigned char	new_c;

	len = ft_strlen(s);
	new_c = (unsigned char)c;
	while ((unsigned char)s[len] != new_c && len > 0)
		len--;
	if ((unsigned char)s[len] == new_c)
		return ((char *)(s + len));
	return (NULL);
}
