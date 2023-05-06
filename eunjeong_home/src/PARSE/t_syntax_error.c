/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_syntax_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:03:50 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/05 12:49:40 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	syntax_error(t_token *cur)
{
	printf("%s, error\n", cur->data);
	g_glob.exit_stat = ERR_UNEXPEC;
	return (FALSE);
}
