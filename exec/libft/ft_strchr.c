/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 01:37:47 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:10:23 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int tofind)
{
	while (*src)
	{
		if (*src == (char)tofind)
			return ((char *)src);
		src++;
	}
	if (*src == (char)tofind)
		return ((char *)src);
	return (NULL);
}
