/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 08:49:06 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/13 12:36:35 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	ft_precision(char (*dst)[BUFF_S], t_printf *lst)
{
	char	tmp[BUFF_S];
	int		precision;

	if (ft_strchr_exist(lst->options, '#') && ft_tolower(lst->flag) == 'x' &&
			lst->precision > 0)
		lst->precision += 2;
	precision = (lst)->precision;
	if (ft_exception(lst) && precision < (int)ft_strlen((*dst)))
		precision = ft_strlen(*dst);
	if (precision >= 0)
	{
		if (ft_exception(lst) && precision > (int)ft_strlen(*dst))
		{
			ft_large(&tmp, precision - (int)ft_strlen(*dst), '0');
			ft_join(&(*dst), tmp, 1);
		}
		else
			while (precision <= BUFF_S)
				(*dst)[precision++] = '\0';
	}
	else if (precision == -1)
		ft_bzero(&(*dst), BUFF_S);
}

void	ft_large_min(char (*dst)[BUFF_S], t_printf *lst, int stock[3])
{
	char	c;
	int		i;
	char	tmp[BUFF_S];

	i = -1;
	c = (ft_strchr_exist(lst->options, '0') && lst->precision < 0) ? '0' : ' ';
	if (ft_strcmp(*dst, "0\0") == 0 && ft_strchr_exist(lst->options, '0') == 0
			&& (lst->large_min == 0 || (lst->precision == -1 ||
					lst->precision == 0)))
		ft_bzero(&(*dst), BUFF_S);
	if (stock[2] > 0)
	{
		if (ft_strchr_exist(lst->options, '-'))
			while (stock[2]-- > 0)
				(*dst)[ft_strlen(*dst) + stock[2]] = ' ';
		else
		{
			while (stock[2] > ++i)
				tmp[i] = c;
			i = 0;
			while (stock[2] < BUFF_S)
				tmp[stock[2]++] = (*dst)[i++];
			ft_cpy_str(&(*dst), tmp);
		}
	}
}

/*
**	stock[0] = plus
**	stock[1] = moins
**	stock[2] = len
*/

void	ft_options(char (*dst)[BUFF_S], t_printf *lst, int stock[3])
{
	char	c;
	char	tmp[BUFF_S];

	c = ' ';
	if ((ft_strchr_exist(lst->options, '0') == 1) && stock[1] == 0)
	{
		c = '0';
		ft_large(&tmp, stock[2], c);
		(stock[2] > 0) ? ft_join(&(*dst), tmp, 1) : 0;
	}
	if (ft_exception(lst))
		manage_plus_decimal(&(*dst), lst, stock);
	if (stock[2] > 0 && c == ' ')
	{
		ft_large(&tmp, stock[2], c);
		(stock[1] == 0) ? ft_join(&(*dst), tmp, 1) :
			ft_join(&(*dst), tmp, 0);
	}
}

void	ft_apply_arg(char *str, t_printf **lst)
{
	char	dst[BUFF_S];
	int		stock[3];

	ft_cpy_str(&dst, str);
	((*lst)->conversion[1] && (*lst)->conversion[1] == 'p') ?
		verif_p(&dst, &(*lst)) : 0;
	((ft_exception(*lst) && ft_strchr_exist(dst, '-') &&
			(*lst)->precision != 0)) ? (*lst)->precision += 1 : 0;
	ft_precision(&(dst), (*lst));
	ft_stock(&(*lst), dst, &stock);
	(*lst)->large_min > ft_strlen(dst) ? ft_large_min(&dst, (*lst), stock) : 0;
	ft_stock(&(*lst), dst, &stock);
	ft_options(&dst, (*lst), stock);
	check_space((*lst), &dst);
	if (ft_exception(*lst))
	{
		if ((*lst)->flag == 'd' || (*lst)->flag == 'i')
		{
			ft_correct(&dst, '-', '0', &(*lst));
			ft_correct_reverse(&dst, '+', ' ');
		}
		else
			ft_correct_x(&dst, 'x', '0');
	}
	ft_display(dst, &(*lst));
}
