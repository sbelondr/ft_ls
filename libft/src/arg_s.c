/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 07:11:11 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/13 12:35:37 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	ft_flag_s_null(t_printf **lst)
{
	char	dst[BUFF_S];
	int		stock[3];

	ft_bzero(&dst, BUFF_S);
	dst[0] = '(';
	dst[1] = 'n';
	dst[2] = 'u';
	dst[3] = 'l';
	dst[4] = 'l';
	dst[5] = ')';
	ft_precision(&dst, (*lst));
	stock[0] = 0;
	stock[1] = ft_strchr_exist((*lst)->options, '-');
	stock[2] = (*lst)->large_min - ft_strlen(dst);
	ft_large_min(&dst, (*lst), stock);
	ft_display(dst, &(*lst));
}

void	ft_arg_s(t_printf **lst)
{
	char	*str;

	if (!(str = ft_strdup(va_arg((*lst)->ap, char*))))
		ft_flag_s_null(&(*lst));
	else
		ft_apply_arg(str, &(*lst));
	ft_strdel(&str);
}

void	ft_fill_char(char (*str)[BUFF_S], int len, int c, int right)
{
	int	len_str;

	len_str = ft_strlen(*str);
	if (right == 0)
		while (len-- > 0)
			ft_startjoin(&(*str), c);
	else
		while (len-- > 0)
			(*str)[len + len_str] = ' ';
}

void	ft_arg_c(t_printf **lst)
{
	char	str[BUFF_S];
	size_t	len;
	int		fill;
	char	is_null;

	ft_bzero(&str, BUFF_S);
	len = 0;
	is_null = 'N';
	fill = (ft_strchr_exist((*lst)->options, '0')) ? '0' : ' ';
	if (!(str[0] = (char)(va_arg((*lst)->ap, int))))
	{
		(*lst)->len += 1;
		is_null = 0;
		len = 1;
	}
	(len == 0) ? len = ft_strlen(str) : 0;
	if ((*lst)->large_min > len)
		ft_fill_char(&str, (*lst)->large_min - len, fill,
				ft_strchr_exist((*lst)->options, '-'));
	ft_display(str, &(*lst));
	(is_null == 0) ? write(1, &is_null, 1) : 0;
}

void	ft_arg_percent(t_printf **lst)
{
	char	str[BUFF_S];

	ft_bzero(&str, BUFF_S);
	str[0] = '%';
	if ((*lst)->precision == 0)
		(*lst)->precision = -2;
	ft_apply_arg(str, &(*lst));
}
