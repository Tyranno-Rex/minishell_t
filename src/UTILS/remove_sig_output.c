/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_signal_output.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:21:01 by minjinki          #+#    #+#             */
/*   Updated: 2023/02/23 15:23:43 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_sig_output(void)
{
	struct termios	ter;

	if (tcgetattr(0, &ter))
		exit_with_code("minishell: tcgetattr\n", 2);
	ter.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &ter))
		exit_with_code("minishell: tcsetattr\n", 2);
}

void	remove_sig2(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
}
