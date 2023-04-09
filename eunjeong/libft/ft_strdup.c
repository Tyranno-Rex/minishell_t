/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjeong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 15:19:10 by eunjeong          #+#    #+#             */
/*   Updated: 2022/07/09 15:19:12 by eunjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*tmp;
	size_t	len;
	size_t	num;

	num = 0;
	len = ft_strlen(src);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (0);
	while (num < len)
	{
		tmp[num] = src[num];
		num++;
	}
	tmp[num] = '\0';
	return (tmp);
}
