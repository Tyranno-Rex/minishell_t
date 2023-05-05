/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:26:40 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/05 12:49:23 by minjinki         ###   ########.fr       */
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
** AST tree
*/
typedef struct s_scmd
{
	char	*ori;
	char	*scmd;
	char	*op;
	char	**av;
}	t_scmd;

typedef struct s_redi
{
	char	*redi;
	char	*av;
}	t_redi;

typedef struct s_reditree
{
	t_redi				*redi;
	struct t_reditree	*reditree;
}	t_reditree;

typedef struct s_cmd
{
	t_redi		*redi;
	t_scmd		*scmd;
	t_reditree	*reditree;
}	t_cmd;

typedef struct s_pipe
{
	t_cmd			*cmd;
	int				fd[2];
	int 			infile;
	int				outfile;
	struct s_pipe	*pipe;
}	t_pipe;

typedef struct s_tree
{
	int		is_here;
	char	*heredoc;
	t_cmd	*cmd;
	t_pipe	*pipe;
}	t_tree;

/*
** global variable
*/
typedef struct s_glob
{
	t_tree	*root;
	char	**env_ori;
	char	*cmd;
	t_token	*tok;
	t_env	*env;
	char	**path;
	int		exit_stat;
}	t_glob;

#endif