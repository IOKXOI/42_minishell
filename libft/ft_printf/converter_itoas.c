/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_itoas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iok <iok@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 05:07:03 by sydauria          #+#    #+#             */
/*   Updated: 2022/10/21 15:39:07 by iok              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*printf_strdup(char *src);

char	*printf_itoa(int n)
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
		return (NULL);
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

char	*ft_itoa_base(int n, char *base)
{
	int				i;
	unsigned int	save;
	char			*num;

	i = 1;
	save = n;
	while (save >= 16 && i++)
		save = save / 16;
	save = n;
	num = malloc(sizeof(char) * (i + 3));
	if (!num)
		return (NULL);
	num[i] = '\0';
	while (i)
	{
		num[--i] = base[(save % 16)];
		save /= 16;
	}
	return (num);
}

char	*ft_itoa_u(size_t n)
{
	int		i;
	size_t	save;
	char	*num;

	i = 1;
	save = n;
	while (save >= 10 && i++)
		save = save / 10;
	save = n;
	num = malloc(sizeof(char) * (i + 1));
	if (!num)
		return (NULL);
	num[i] = '\0';
	while (i)
	{
		num[--i] = (save % 10 + '0');
		save /= 10;
	}
	return (num);
}

char	*ft_itoa_base_u(size_t n, char *base)
{
	int				i;
	size_t			save;
	char			*num;

	i = 3;
	save = n;
	if (!n)
		return (printf_strdup("(nil)"));
	while (save >= 16 && i++)
		save = save / 16;
	num = malloc(sizeof(char) * (i + 1));
	if (!num)
		return (NULL);
	num[i] = '\0';
	while (i > 1)
	{
		num[--i] = base[(n % 16)];
		n /= 16;
	}
	num[0] = '0';
	num[1] = 'x';
	return (num);
}
