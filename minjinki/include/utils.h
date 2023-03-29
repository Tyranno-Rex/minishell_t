/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:22:34 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/20 17:03:26 by minjinki         ###   ########.fr       */
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
t_bool	free_all(void);
void	free_cmd(char *cmd);
void	free_matrix(char **matrix);
t_bool	ft_free(void *av);

/*
** linked_list.c
*/

#endif