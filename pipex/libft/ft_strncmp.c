/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 03:39:54 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:11:56 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;
	int		diff;

	i = 0;
	if (length == 0)
		return (0);
	while (first[i] && (first[i] == second[i]) && --length)
		i++;
	diff = ((unsigned char)first[i] - (unsigned char)second[i]);
	if (diff > 0)
		return (1);
	if (diff < 0)
		return (-1);
	return (0);
}

int	ft_strcmp(const char *first, const char *second)
{
	size_t	i;
	int		diff;

	i = 0;
	while (first[i] && (first[i] == second[i]))
		i++;
	diff = ((unsigned char)first[i] - (unsigned char)second[i]);
	if (diff > 0)
		return (1);
	if (diff < 0)
		return (-1);
	return (0);
}
