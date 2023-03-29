/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_root_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:45:32 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/25 16:52:40 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	init_root(void)
{
	g_glob.root = ft_calloc(1, sizeof(t_tree));
	if (!(g_glob.root))
		return (FALSE);
	g_glob.root->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!(g_glob.root->cmd))
		return (FALSE);
}
