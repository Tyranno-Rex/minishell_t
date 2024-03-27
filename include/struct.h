/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 09:31:36 by MJKim             #+#    #+#             */
/*   Updated: 2023/03/11 18:05:30 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_type
{
	T_NULL,
	T_STR,
	T_PIPE,
	T_REDI,
	T_DOUBLE,
	T_SINGLE
}	t_type;

/*****************************************************************
 ** s_data														**
 **																**
 ** struct to use as global variable  		      				**
 ** orgin_env: env before pasing								**
 *****************************************************************/

typedef struct s_data
{
	char	**origin_env;
	t_env	*env
	t_token	*tok;
	t_lexer	*lex;
}	t_data;

/*****************************************************************
 ** s_env														**
 **																**
 ** struct to save environment variables    					**
 ** key: save key(e.g. HOME)									**
 ** t_value : struct to save value(e.g. /Users/minjinki)		**
 ** 		: as some keys have more than one values,
 **			: such as PATH
 **			: so we implemented value as a struct				**
 *****************************************************************/

typedef struct s_env
{
	char			*key;
	t_value			*value;	
	struct s_env	*next;
}	t_env;

typedef struct s_value
{
	char			*val;
	struct s_value	*next;
}	t_value;

/*****************************************************************
** s_token														**
** tokenize input commands										**
*****************************************************************/

typedef struct s_token
{
	int				*s;
	struct s_token	*next;
}	t_token;

/*****************************************************************
** s_lexer														**
** tokenize input commands										**
*****************************************************************/

typedef struct s_lexer
{
}	t_lexer;

#endif