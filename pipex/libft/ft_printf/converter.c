/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iok <iok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:58:51 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/21 15:36:20 by iok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_getchar(char c, t_struct *data)
{
	char	*formated;

	if (!c)
		data->null_char = 1;
	formated = malloc(2);
	if (!formated)
		return (NULL);
	formated[0] = c;
	formated[1] = '\0';
	return (formated);
}

static char	*ft_get_address(void *ptr)
{
	size_t	address;
	char	*formated;

	address = (size_t)ptr;
	formated = ft_itoa_base_u(address, "0123456789abcdef");
	return (formated);
}

char	*converter(const char *format, t_struct *data, va_list args)
{
	size_t	i;
	char	*formated;

	i = data->form_offset + 1;
	if (format[i] == 'c')
		formated = ft_getchar(va_arg(args, int), data);
	else if (format[i] == 's')
		formated = printf_strdup(va_arg(args, char *));
	else if (format[i] == 'd' || format[i] == 'i')
		formated = printf_itoa(va_arg(args, int));
	else if (format[i] == 'u')
		formated = ft_itoa_u(va_arg(args, unsigned int));
	else if (format[i] == 'x')
		formated = ft_itoa_base(va_arg(args, int), "0123456789abcdef");
	else if (format[i] == 'X')
		formated = ft_itoa_base(va_arg(args, int), "0123456789ABCDEF");
	else if (format[i] == 'p')
		formated = ft_get_address(va_arg(args, void *));
	else if (format[i] == '%')
		formated = ft_getchar('%', data);
	else
		formated = (printf_strndup((const char *)&format[i - 1], 2));
	data->form_offset = (i + 1);
	return (formated);
}
