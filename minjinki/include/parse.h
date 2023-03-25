/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:25:20 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/25 18:38:12 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"

/*
** parse.c
*/
void	parse(char *cmd);
t_bool	is_space_only(char *cmd);

/*
** t_quotes.c
*/
void	deal_quotes(char *cmd);
t_token	*malloc_node(void);

/*
** t_spaces.c
*/
void	deal_spaces(void);
t_bool	add_quotes(t_token **tmp, t_token *cur);

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