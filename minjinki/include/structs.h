/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:26:40 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/23 19:24:33 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "define.h"

/*
** linked list for tokenization
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
typedef struct s_env
{
	char			*key;
	char			*val;
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
	char	**path;
}	t_glob;

/*
** AST tree
*/
typedef struct s_scmd;
{
	char	*ori;
	char	*scmd;
	char	*op;
	char	**av;
}	t_scmd;

typedef struct s_rdata
{
	char	*redi;
	char	*av;
}	t_rdata;

typedef struct s_redi
{
	t_rdata			*rdata;
	struct t_redi	*redi;
};

typedef struct s_cmd
{
	t_scmd	*scmd;
	t_redi	*redi;
}	t_cmd;

typedef struct s_pipe
{
	t_cmd			*cmd;
	int				fd[2];
	struct s_pipe	*pipe;
}	t_pipe;

typedef struct s_tree
{
	int		is_here;
	char	*heredoc;
	t_cmd	*cmd;
	t_pipe	*pipe;
}	t_tree;

#endif