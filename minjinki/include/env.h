/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:11:08 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/23 19:13:45 by minjinki         ###   ########.fr       */
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
** env_utils.c
*/
t_env	*env_lstnew(char *key);
void	env_lstadd_back(t_env **lst, t_env *new);
t_bool	env_lstclear(t_env **lst);
void	env_lstprint(void);

/*
** val_utils.c
*/
t_val	*val_lstnew(char *val);
void	val_lstadd_back(t_env *env, t_val *new);
void	val_lstclear(t_val **val);

#endif