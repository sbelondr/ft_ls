/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:30:54 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/12 16:05:16 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_printf.h"

void		ft_startjoin(char (*str)[BUFF_S], char c)
{
	int		len;

	len = ft_strlen(*str);
	if (len == BUFF_SIZE)
		return ;
	while (--len >= 0)
		(*str)[len + 1] = (*str)[len];
	(*str)[0] = c;
}

void		ft_convert_base(unsigned int nb, int base, char (*str)[BUFF_S])
{
	unsigned int	result;
	char			c;

	ft_bzero(&(*str), BUFF_SIZE);
	while (nb != 0)
	{
		result = nb % base;
		nb /= base;
		if (result > 9)
			c = ft_alpha(result);
		else
			c = result + '0';
		ft_startjoin(&(*str), c);
	}
}

void		ft_convert_base_uc(unsigned char nb, int base, char (*str)[BUFF_S])
{
	unsigned char	result;
	char			c;

	ft_bzero(&(*str), BUFF_SIZE);
	while (nb != 0)
	{
		result = nb % base;
		nb /= base;
		if (result > 9)
			c = ft_alpha(result);
		else
			c = result + '0';
		ft_startjoin(&(*str), c);
	}
}

void		ft_convert_base_us(unsigned short nb, int base, char (*str)[BUFF_S])
{
	unsigned short	result;
	char			c;

	ft_bzero(&(*str), BUFF_SIZE);
	while (nb != 0)
	{
		result = nb % base;
		nb /= base;
		if (result > 9)
			c = ft_alpha(result);
		else
			c = result + '0';
		ft_startjoin(&(*str), c);
	}
}

void		ft_convert_base_ll(unsigned long long nb, int base,
		char (*str)[BUFF_S])
{
	unsigned long long	result;
	char				c;

	ft_bzero(&(*str), BUFF_SIZE);
	while (nb != 0)
	{
		result = nb % base;
		nb /= base;
		if (result > 9)
			c = ft_alpha(result);
		else
			c = result + '0';
		ft_startjoin(&(*str), c);
	}
}
