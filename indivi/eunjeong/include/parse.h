/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:25:20 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/08 17:17:06 by minjinki         ###   ########.fr       */
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

t_bool	chk_cmd_is_valid(void);
t_bool	syntax_error(t_token *pre, t_token *cur);
t_bool	merge_n_split_nodes(t_token **tok);

/*
** l_init_tree.c
*/
t_bool	init_tree(void);

/*
** l_cmd.c
*/
t_cmd	*add_cmd(t_token *token);

/*
** l_scmd.c
*/
t_scmd	add_scmd(t_token *token);

/*
** l_reditree.c
*/
t_reditree	*add_reditree(t_token *token);

/*
** l_put_token_to_tree.c
*/
t_bool	lexer(void);

#endif