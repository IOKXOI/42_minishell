/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 01:05:05 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:05:36 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int				i;
	int				sign;
	unsigned int	save;
	char			*num;

	i = 1;
	sign = 1;
	if (n < 0 && i++)
		sign = -1;
	save = n * sign;
	while (save >= 10 && i++)
		save = save / 10;
	save = n * sign;
	num = malloc(sizeof(char) * (i + 1));
	if (!num)
		return (perror("ft_itoa : malloc"), NULL);
	num[i] = '\0';
	while (i)
	{
		num[--i] = (save % 10 + '0');
		save /= 10;
	}
	if (n < 0)
		num[0] = '-';
	return (num);
}
