/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 09:24:34 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:11:01 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest;
	size_t	source;
	size_t	i;

	dest = ft_strlen(dst);
	source = ft_strlen((char *)src);
	if (size <= dest)
		return (source + size);
	i = 0;
	while (*src && dest + i < (size - 1))
	{
		dst[dest + i] = (char) *src++;
		i++;
	}
	dst[dest + i] = '\0';
	return (dest + source);
}
