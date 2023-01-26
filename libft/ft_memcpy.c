/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:22:45 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:07:49 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	void	*dst;

	if (!dest && !src)
		return (NULL);
	dst = dest;
	while (size--)
		*(char *)dest++ = *(char *)src++;
	return (dst);
}
