/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:11:08 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/04 14:38:07 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "structs.h"

/*
** init_env.c
*/
t_bool	init_env(char ***env);
t_bool	copy_env(char ***env);

/*
** parse_env.c
*/
t_bool	parse_env(char ***env);

/*
** deal_env.c
*/
t_bool	deal_env(t_token *token);

/*
** env_utils.c
*/
t_env	*env_lstnew(char *key, char *value);
void	env_lstadd_back(t_env **lst, t_env *new);
t_bool	env_lstclear(t_env **lst);
void	env_lstprint(void);

/*
** env_utils2.c
*/
t_env	*env_search_key(char *key);

#endif