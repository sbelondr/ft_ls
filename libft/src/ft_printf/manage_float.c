/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 21:24:41 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/12 14:26:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf.h"

/*
** https://ryanstutorials.net/binary-tutorial/binary-floating-point.php
*/

void	div_float(char (*tab)[BUFF_S], int d)
{
	int		j;
	int		stock[2];
	char	result[BUFF_S];

	if ((*tab)[0] == '0')
		return ;
	d += 1;
	ft_bzero(&(*tab), BUFF_S);
	ft_pow_array_fix(d, &result);
	while (--d > 0)
	{
		j = -1;
		stock[1] = 0;
		while (result[++j])
		{
			stock[0] = ((result[j] - '0') * 10) / 2;
			result[j] = ((stock[0] / 10) + stock[1]) + '0';
			stock[1] = stock[0] % 10;
		}
	}
	ft_cpy_str(&(*tab), result);
}

void	manage_mantissa(char (*tab)[BUFF_S])
{
	char	result[BUFF_S];
	char	tmp[BUFF_S];
	int		i;
	int		j;

	i = -1;
	j = ft_strlen(*tab) - 1;
	ft_bzero(&result, BUFF_S);
	result[0] = '0';
	while ((*tab)[++i])
	{
		ft_bzero(&tmp, BUFF_S);
		tmp[0] = (*tab)[i];
		mult_mantissa(&tmp, --j);
		add_mantissa(&result, tmp);
	}
	ft_bzero(&(*tab), BUFF_S);
	ft_cpy_str(&(*tab), result);
}

void	manage_float(char (*tab)[BUFF_S])
{
	char	result[BUFF_S];
	char	tmp[BUFF_S];
	int		i;

	i = -1;
	ft_bzero(&result, BUFF_S);
	result[0] = '0';
	while ((*tab)[++i])
	{
		ft_bzero(&tmp, BUFF_S);
		tmp[0] = (*tab)[i];
		div_float(&tmp, i);
		add_float(&result, &tmp);
	}
	ft_bzero(&(*tab), BUFF_S);
	ft_cpy_str(&(*tab), result);
}

void	ft_gest_float(char (*tab)[BUFF_S], int d)
{
	char	mantissa[BUFF_S];
	char	float_c[BUFF_S];

	d += 1;
	ft_reverse_tablo(&(*tab));
	ft_strsub_tab_fix(&mantissa, (*tab), 0, d);
	if ((int)ft_strlen(mantissa) < d)
		ft_add_zero(&mantissa, d - ft_strlen(mantissa));
	ft_strsub_tab_fix(&float_c, (*tab), d, ft_strlen((*tab)));
	manage_mantissa(&mantissa);
	manage_float(&float_c);
	ft_bzero(&(*tab), BUFF_S);
	ft_join(&(*tab), mantissa, 0);
	ft_join(&(*tab), ".\0", 0);
	ft_join(&(*tab), float_c, 0);
}
