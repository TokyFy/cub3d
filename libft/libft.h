/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sravonin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:07:41 by sravonin          #+#    #+#             */
/*   Updated: 2024/03/16 16:18:10 by sravonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

char	*ft_itoa(int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_isalpha(int c);
void	*ft_memset(void *s, int c, size_t n);
int		ft_tolower(int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_toupper(int c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
