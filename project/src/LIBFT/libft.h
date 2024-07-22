/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:25:24 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/05 14:21:14 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include "../../include/structs.h"

char	*do_join(char *s1, char *s2);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s1, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_is_space(char c);
int		ft_lstsize(t_token *lst);
int		ft_matrixlen(char **matrix);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);

size_t	ft_strlcat(char *dst, const char *src, size_t destsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t destsize);
size_t	ft_strlen(const char *s);
size_t	ft_strnlen(char *s, int c);

t_bool	ft_lstadd_back(t_token **lst, t_token *new);

t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstmap(t_token *lst, void *(*f)(void *));
t_token	*ft_lstnew(int type, char *s);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_lstadd_front(t_token **lst, t_token *new);
void	ft_lstclear(t_token **lst);
void	ft_lstdelone(t_token *lst);
void	ft_lstiter(t_token *lst, void (*f)(void *));
void	ft_lstinsert(t_token *pre, t_token *new);
void	ft_lstremove(t_token *pre, t_token *del);
void	ft_lstprint(t_token **lst);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

#endif
