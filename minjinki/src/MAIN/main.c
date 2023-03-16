/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:02 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/16 14:27:11 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
		exit_with_code("usage: ./minishell\n", 126);
	copy_env(&env);
	free_all();
}
