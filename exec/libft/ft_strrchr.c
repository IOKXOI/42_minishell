/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 01:50:34 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:12:20 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int tofind)
{
	size_t	len;

	len = ft_strlen(src);
	if (tofind == '\0')
		return ((char *)&src[len]);
	while (len--)
	{
		if (src[len] == (char)tofind)
			return ((char *)&src[len]);
	}
	return (NULL);
}
