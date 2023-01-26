/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:18:02 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:08:00 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (src > dest && size--)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	while (dest > src && size--)
		*(unsigned char *)(dest + size) = *(unsigned char *)(src + size);
	return (dest);
}
