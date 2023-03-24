/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:25:20 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/23 12:21:29 by minjinki         ###   ########.fr       */
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

#endif