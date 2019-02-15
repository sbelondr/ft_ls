/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 11:18:43 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/13 12:37:28 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

char		ft_alpha(unsigned int nb)
{
	char	c;

	c = 55 + nb;
	return (c);
}

void		ft_correct_reverse(char (*dst)[BUFF_S], char a, char b)
{
	int	index_a;
	int	index_b;
	int	i;

	i = 0;
	index_a = ft_chr_index((*dst), a);
	index_b = -1;
	while (++i < BUFF_S)
	{
		if ((*dst)[i] == b)
			index_b = i;
		else
			break ;
	}
	if (index_b != -1 && index_a != -1 && index_a < index_b)
	{
		(*dst)[index_a] = b;
		(*dst)[index_b] = a;
	}
}

void		ft_startjoin_50(char (*str)[50], char c)
{
	int		len;

	len = ft_strlen(*str);
	if (len == BUFF_SIZE)
		return ;
	while (--len >= 0)
		(*str)[len + 1] = (*str)[len];
	(*str)[0] = c;
}

void		result_null(t_printf **lst, char (*str)[BUFF_S])
{
	if ((*lst)->precision == -2 || (*lst)->precision > 0 ||
			(ft_strchr_exist((*lst)->options, '#') && (*lst)->flag == 'o') ||
			((*lst)->conversion[1] && (*lst)->conversion[1] == 'p'))
	{
		(*str)[0] = '0';
		if ((*lst)->conversion[1] && (*lst)->conversion[1] == 'p')
		{
			(*str)[1] = 'x';
			if ((*lst)->precision > 0)
				(*str)[2] = '0';
		}
	}
	if (ft_strchr_exist((*lst)->options, '#') && ((*lst)->precision == -1 ||
			(*lst)->precision == 0) && ft_tolower((*lst)->flag) == 'o')
		(*lst)->precision = -2;
}

void		ft_correct_x(char (*dst)[BUFF_S], char a, char b)
{
	int	index_a;
	int	index_b;

	index_a = ft_chr_index((*dst), a);
	if (index_a == -1)
	{
		a = ft_toupper(a);
		index_a = ft_chr_index((*dst), a);
	}
	index_b = ft_chr_index((*dst), b);
	if (index_b > -1 && (*dst)[index_b + 1] == b)
		index_b++;
	if (index_a != -1 && index_b != -1 && index_a > index_b &&
			(index_a - 1 >= 0 && (*dst)[index_b - 1] == b))
	{
		(*dst)[index_b] = a;
		(*dst)[index_a] = b;
	}
}
