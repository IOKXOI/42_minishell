/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:32:32 by sydauria          #+#    #+#             */
/*   Updated: 2023/02/03 21:16:34 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *buffer, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	if (buffer)
	{
		str = malloc(sizeof(char) * n + 1);
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
