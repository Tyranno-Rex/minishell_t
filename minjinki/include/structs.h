/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:26:40 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/23 17:55:06 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "define.h"

/*
** linked list for tokenize
*/
typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
}	t_token;

/*
** linked list for parse env
*/
typedef struct s_val
{
	char			*val;
	struct s_val	*next;
}	t_val;

typedef struct s_env
{
	char			*key;
	t_val			*val;
	struct s_env	*next;
}	t_env;

/*
** global variable
*/
typedef struct s_glob
{
	char	**env_ori;
	char	*cmd;
	t_token	*tok;
	t_env	*env;
}	t_glob;

#endif