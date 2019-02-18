/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_arg_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:11:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/13 12:36:41 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	ft_apply_round(char (*dst)[BUFF_S], int stock, int precision)
{
	int	i;
	int	j;

	i = ft_chr_index((*dst), '.');
	j = 0;
	if (i != -1)
	{
		while ((*dst)[i + j] && j <= precision)
			j++;
		while ((i + j) < BUFF_S && j <= precision)
			(*dst)[i + j++] = '0';
		i += j;
	}
	i = (i == -1) ? ft_strlen(*dst) - 1 : i - 1;
	stock = (stock > 4) ? 1 : 0;
	while (stock > 0)
	{
		if ((*dst)[i] != '.')
		{
			stock += ((*dst)[i] - '0');
			(*dst)[i] = (stock % 10) + '0';
			stock /= 10;
		}
		i--;
	}
}

void	ft_round_precision(char (*dst)[BUFF_S], int precision)
{
	int	i;
	int	j;
	int	stock;

	precision = (precision == -2) ? 6 : precision;
	i = 0;
	j = 0;
	stock = -1;
	while ((*dst)[i] && (*dst)[i] != '.')
		i++;
	if (precision == 0 || precision == -1)
	{
		stock = ((*dst)[i + 1] - '0') - ((*dst)[i + 2] - '0' == 0 ? 1 : 0);
		while ((*dst)[i])
			(*dst)[i++] = '\0';
	}
	else
		while ((*dst)[i + j] && j < precision)
			j++;
	if (stock == -1)
		stock = (*dst)[i + precision + 1] ? (*dst)[i + precision + 1] - '0' : 0;
	i += j;
	while ((*dst)[++i])
		(*dst)[i] = '\0';
	ft_apply_round(&(*dst), stock, precision);
}

void	ft_precision_float(char (*dst)[BUFF_S], t_printf **lst)
{
	ft_round_precision(&(*dst), (*lst)->precision);
	if ((*lst)->precision != -2 && ft_strchr_exist((*lst)->options, '#'))
		(*dst)[ft_strlen(*dst)] = '.';
}

void	ft_options_float(char (*dst)[BUFF_S], t_printf **lst, int stock[3])
{
	char	c;
	int		len;

	c = (ft_strchr_exist((*lst)->options, '0')) ? '0' : ' ';
	len = (int)(*lst)->large_min - (int)ft_strlen(*dst);
	ft_large_min_float(len, c, &(*dst));
	if (ft_strchr_exist((*lst)->options, ' ') &&
			ft_strchr_exist((*dst), '-') == 0)
	{
		(len < 1 || (len > 0 && c == ' ')) ? ft_deplace(&(*dst)) : 0;
		(*dst)[0] = ' ';
	}
	if (stock[0] == 1 && ft_strchr_exist((*dst), '-') == 0)
	{
		(len < 1 || (len > 0 && c == ' ')) ? ft_deplace(&(*dst)) : 0;
		len = ft_strlen(*dst) - 1;
		((*dst)[len] == ' ') ? (*dst)[len] = '\0' : 0;
		(*dst)[0] = '+';
	}
}

void	ft_apply_arg_float(char (*str)[BUFF_S], t_printf **lst)
{
	int	stock[3];

	ft_stock(&(*lst), (*str), &stock);
	ft_inf_nan(&(*str), &(*lst), stock);
	ft_precision_float(&(*str), &(*lst));
	ft_options_float(&(*str), &(*lst), stock);
	ft_correct(&(*str), '-', '0', &(*lst));
	ft_display((*str), &(*lst));
}
