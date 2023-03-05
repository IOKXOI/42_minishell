/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iok <iok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:08:41 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/21 15:37:59 by iok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_struct
{
	int		null_char;
	size_t	form_offset;
	size_t	buff_offset;
	size_t	wrote;
}	t_struct;

int		ft_printf(const char *format, ...);
int		check_format(const char *format);
char	*printf_strdup(char *src);
char	*printf_strndup(const char *src, int n);
char	*printf_itoa(int n);
char	*ft_itoa_base(int n, char *base);
char	*ft_itoa_u(size_t n);
char	*ft_itoa_base_u(size_t n, char *base);
char	*converter(const char *format, t_struct *data, va_list args);

#endif
