/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 05:45:17 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/31 12:51:09 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *str)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc(ft_strlen(str) + 1);
	if (new == NULL)
		return (NULL);
	while (*str)
		new[i++] = *str++;
	new[i] = 0x00;
	return (new);
}
