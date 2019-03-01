/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_float.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:43:47 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/21 22:04:25 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf.h"

void	add_apply(int stock, char (*tab)[BUFF_S], int i)
{
	while (stock > 0)
	{
		if (--i < 0)
		{
			ft_deplace(&(*tab));
			(*tab)[0] = (stock % 10) + '0';
		}
		else
		{
			stock = ((*tab)[i] - '0') + stock;
			(*tab)[i] = (stock % 10) + '0';
		}
		stock /= 10;
	}
}

void	add_mantissa(char (*tab)[BUFF_S], char tab_b[BUFF_S])
{
	int	i;
	int	len_b;
	int	stock;

	i = ft_strlen(*tab);
	len_b = ft_strlen(tab_b);
	stock = 0;
	while (--len_b >= 0)
	{
		if (--i >= 0)
		{
			stock += ((tab_b[len_b] - '0') + ((*tab)[i] - '0'));
			(*tab)[i] = (stock % 10) + '0';
		}
		else
		{
			ft_deplace(&(*tab));
			(*tab)[0] = (((tab_b[len_b] - '0') + stock) % 10) + '0';
		}
		(stock != 0) ? stock /= 10 : 0;
	}
	add_apply(stock, &(*tab), i);
}

void	ft_add_zero(char (*tab)[BUFF_S], int len)
{
	int	i;

	i = ft_strlen(*tab);
	while (len--)
		(*tab)[i++] = '0';
}

void	add_float(char (*tab)[BUFF_S], char (*tab_b)[BUFF_S])
{
	int	len;
	int	len_b;

	len = ft_strlen(*tab);
	len_b = ft_strlen(*tab_b);
	if (len == len_b)
		add_mantissa(&(*tab), (*tab_b));
	else if (len > len_b)
	{
		ft_add_zero(&(*tab_b), len - len_b);
		add_mantissa(&(*tab), (*tab_b));
	}
	else
	{
		ft_add_zero(&(*tab), len_b - len);
		add_mantissa(&(*tab), (*tab_b));
	}
}
