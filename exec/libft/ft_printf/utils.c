/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iok <iok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 04:05:40 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/20 17:50:59 by iok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	printf_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*printf_strdup(char *src)
{
	char	*dest;
	size_t	i;

	if (!src)
		return (printf_strdup("(null)"));
	i = 0;
	dest = malloc(sizeof(char) * (printf_strlen(src) + 1));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*printf_strndup(const char *src, int n)
{
	char	*dest;
	size_t	i;

	if (!src)
		return (printf_strdup("(null)"));
	i = 0;
	dest = malloc(sizeof(char) * n);
	if (!dest)
		return (NULL);
	while (n)
	{
		dest[i] = src[i];
		i++;
		n--;
	}
	dest[i] = '\0';
	return (dest);
}

int	check_format(const char *format)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (format[i] == '%' || format[i] == ' '
		|| (format[i] >= 8 && format[i] <= 13))
	{
		if (format[i] == '%')
			count++;
		i++;
	}
	if (count == 1 && !format[i])
		return (0);
	return (1);
}
