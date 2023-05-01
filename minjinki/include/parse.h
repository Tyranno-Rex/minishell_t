/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:25:20 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/01 16:32:53 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"

/*
** parse.c
*/
t_bool	parse(char *cmd);
t_bool	is_space_only(char *cmd);

/*
** t_quotes.c
*/
t_bool	deal_quotes(char *cmd, int i);
t_token	*malloc_node(void);

/*
** t_spaces.c
*/
t_bool	deal_spaces(void);
t_bool	add_quotes(t_token **tmp, t_token *cur);

/*
** t_pipe_n_redi.c
*/
t_bool	deal_pipe_n_redi(void);

/*
** t_set_pipe_n_redi.c
*/
t_bool	set_pipe_n_redi(void);

/*
** l_make_tree.c
*/
t_bool	make_ast_tree(void);

/*
** l_root_utils.c
*/
t_bool	init_root(void);

/*
** l_put_token_to_tree.c
*/
t_bool	lexer(void);

#endif