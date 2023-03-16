/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:16:51 by minjinki          #+#    #+#             */
/*   Updated: 2022/07/15 16:06:09 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			minus;
	long long	ans;
	size_t		i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	minus = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			minus = -1;
	ans = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		ans = ans * 10 + (str[i] - '0');
		i++;
	}
	return (minus * ans);
}
