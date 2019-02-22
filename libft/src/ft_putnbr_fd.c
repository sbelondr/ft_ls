/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 21:00:04 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:26:20 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr > 0)
	{
		if (nbr / 10 != 0)
			ft_putnbr_fd(nbr / 10, fd);
		c = (nbr % 10) + '0';
		ft_putchar_fd(c, fd);
	}
	if (nbr == 0)
		ft_putchar_fd('0', fd);
}
