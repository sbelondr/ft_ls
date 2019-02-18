/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:40:49 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/13 12:39:06 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	ft_round_final(char (*tab)[BUFF_S])
{
	int	i;
	int	j;

	i = ft_strlen(*tab) - 1;
	j = 0;
	while ((*tab)[i] && (*tab)[i] == '0')
		i--;
	while ((*tab)[i - j] && (*tab)[i - j] == '9')
		j++;
	if (j > 0 && !(i == 1 && j == 1))
	{
		i -= j;
		while (j > 0)
			(*tab)[i + j--] = '0';
		(*tab)[i] = (((*tab)[i] - '0') + 1) + '0';
	}
}

void	ft_round_str(char (*tab)[BUFF_S], int round)
{
	int		len;
	int		stock;

	len = ft_strlen(*tab);
	if (len < round)
	{
		ft_add_zero(&(*tab), round - len);
		len = ft_strlen(*tab);
	}
	stock = 0;
	while (--len > 0)
	{
		stock += (*tab)[len] - '0';
		stock = (stock >= 5) ? 1 : 0;
		stock += (*tab)[len - 1] - '0';
		(*tab)[len - 1] = (stock % 10) + '0';
		stock /= 10;
	}
}
