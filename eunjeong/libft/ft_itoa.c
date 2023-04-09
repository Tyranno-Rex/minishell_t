/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjeong <eunjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 19:45:17 by marvin            #+#    #+#             */
/*   Updated: 2022/07/25 16:54:51 by eunjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*func_arr(char *c, unsigned int number, int len)
{
	while (number > 0)
	{
		c[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (c);
}

int	func_len(int n)
{
	int		len;

	len = 0;
	if (n <= 0)
		len += 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int		number;
	long int			len;
	char				*result;
	int					sign;

	sign = 1;
	len = func_len(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!(result))
		return (NULL);
	result[len--] = '\0';
	if (n == 0)
		result[0] = '0';
	if (n < 0)
	{
		sign *= -1;
		number = n * -1;
		result[0] = '-';
	}
	else
		number = n;
	result = func_arr(result, number, len);
	return (result);
}
