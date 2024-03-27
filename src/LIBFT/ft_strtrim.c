/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:16:00 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/11 15:59:12 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		front; // size_t로 되어 있으면 밑에 rear == -1이 비교 불가능하지.. 바보야
	int		rear;

	if (!s1 || !set)
		return (NULL);
	front = 0;
	rear = ft_strlen(s1) - 1;
	while (s1[front] && ft_strchr(set, s1[front]))
		front++;
	if (front > rear || rear == -1)
		return (ft_strdup(""));
	while (s1[rear] && ft_strchr(set, s1[rear]))
		rear--;
	res = (char *)malloc(sizeof(char) * (rear - front + 2));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + front, rear - front + 2);
	return (res);
}
