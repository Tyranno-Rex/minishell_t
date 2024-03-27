/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:45:02 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/11 15:57:44 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static long	ft_convert(int n)
{
	long	new_n;

	if (n < 0)
		new_n = -(long)n;
	else
		new_n = (long)n;
	return (new_n);
}

static int	ft_count_digit(int n)
{
	size_t	digit;

	digit = 0;
	while (n)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	new_n;
	size_t	len;

	if (n == 0)
		return (ft_strdup("0"));
	new_n = ft_convert(n);
	len = ft_count_digit(n);
	if (n < 0)
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	while (new_n)
	{
		res[len] = new_n % 10 + '0';
		new_n /= 10;
		len--;
	}
	if (n < 0)
		res[len] = '-';
	return (res);
}
