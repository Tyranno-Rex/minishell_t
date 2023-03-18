/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:26:40 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/18 13:18:53 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "define.h"

/*
** linked list: for tokenize
*/
typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
}	t_token;

/*
** global variable
*/
typedef struct s_glob
{
	char	**env;
	t_token	*tok;
}	t_glob;

#endif