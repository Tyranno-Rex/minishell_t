/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:36:11 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/11 15:59:09 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
