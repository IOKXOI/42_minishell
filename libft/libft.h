/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iok <iok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 04:35:12 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/21 15:35:51 by iok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include<unistd.h>
# include<stdlib.h>
# include<errno.h>
# include<stdio.h>
# include<stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_struct
{
	int		null_char;
	size_t	form_offset;
	size_t	buff_offset;
	size_t	wrote;
}	t_struct;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isalnum(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_strndup(char *buffer, size_t n);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
char	*ft_strchr(const char *src, int tofind);
char	*ft_strrchr(const char *src, int tofind);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_join_and_free_1(char *s1, char *s2, int a, int b);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size );
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memset(void *ptr, int val, size_t count);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t size);
int		ft_atoi(const char *str);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
int		ft_strncmp(const char *first, const char *second, size_t length);
int		ft_strcmp(const char *first, const char *second);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nbr, int fd);

int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char	*get_next_line(int fd);

//FT_PRINTF//////////////////////////////////////////////////////////////////
int		ft_printf(const char *format, ...);
int		check_format(const char *format);
char	*printf_strdup(char *src);
char	*printf_strndup(const char *src, int n);
char	*printf_itoa(int n);
char	*ft_itoa_base(int n, char *base);
char	*ft_itoa_u(size_t n);
char	*ft_itoa_base_u(size_t n, char *base);
char	*converter(const char *format, t_struct *data, va_list args);
////////////////////////////////////////////////////////////////////////////

#endif
