/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:10:48 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/23 15:11:29 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(char *s, int c)
{
	int	len;

	len = -1;
	while (s[++len])
	{
		if (s[len] == (char)c)
			return (len);
	}
	if (s[len] == '\0')
		return (len);
	return (ERROR);
}
