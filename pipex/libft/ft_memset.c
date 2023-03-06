/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 23:17:05 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:08:34 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int val, size_t count)
{
	unsigned char	*ss;

	ss = ptr;
	while (count--)
		*(unsigned char *)ss++ = val;
	return (ptr);
}
