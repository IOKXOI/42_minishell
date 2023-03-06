/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 05:49:57 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:07:35 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t size)
{
	if (!size)
		return (0);
	while ((*(unsigned char *) ptr1) == (*(unsigned char *) ptr2) && --size)
	{
		ptr1++;
		ptr2++;
	}
	return (*(unsigned char *) ptr1 - (*(unsigned char *) ptr2));
}
