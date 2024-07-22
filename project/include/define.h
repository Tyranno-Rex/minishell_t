/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:30:38 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/05 12:49:10 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define TRUE 1
# define FALSE 0
# define ERROR -1

# define SUCCESS 0
# define FAILURE 1

# define NONE 0
# define STR 1
# define CMD 2
# define DOUBLE 34
# define SINGLE 39
# define PIPE 124
# define LREDI 60		// <
# define HEREDOC 6060	// <<
# define RREDI 62		// >
# define RRREDI 6262	// >>
# define FILES 3
# define OPT 4
# define ARGV 5
# define TMP 6
# define SPACES 7

# define ERR_UNEXPEC 258

typedef int		t_bool;

#endif