/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 07:29:18 by sydauria          #+#    #+#             */
/*   Updated: 2022/08/26 07:36:25 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *buffer, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	if (buffer)
	{
		str = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
		if (!str)
			return (NULL);
		while (*(buffer + i) && i <= n)
		{
			*(str + i) = *(buffer + i);
			i++;
		}
		*(str + i) = '\0';
		return (str);
	}
	return (NULL);
}
