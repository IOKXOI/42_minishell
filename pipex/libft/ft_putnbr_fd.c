/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 01:09:47 by sydauria          #+#    #+#             */
/*   Updated: 2021/12/20 01:09:54 by sydauria         ##   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nbr, int fd)
{
	unsigned int	unb;

	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr *= -1;
	}
	unb = (unsigned)nbr;
	if (unb >= 10)
		ft_putnbr_fd(unb / 10, fd);
	ft_putchar_fd(unb % 10 + '0', fd);
}
