/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:22:34 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/16 14:23:48 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
** error.c
*/
void	exit_with_code(char *s, int errno);
t_bool	print_error(char *s);

/*
** free.c
*/
void	free_all(void);
void	free_matrix(char **matrix);

#endif