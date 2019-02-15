/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:59:28 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/13 12:37:37 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	ft_inf_nan(char (*str)[BUFF_S], t_printf **lst, int stock[3])
{
	int	len;

	len = ft_strlen(*str);
	if ((*str)[len - 1] != 'n' && (*str)[len - 1] != 'f')
		return ;
	ft_large_min(&(*str), (*lst), stock);
}

void	ft_large_min_float(int len, char c, char (*dst)[BUFF_S])
{
	int		i;
	char	tmp[BUFF_S];

	if (len > 0)
	{
		i = -1;
		ft_bzero(&tmp, BUFF_S);
		while (++i < len)
			tmp[i] = c;
		(c == '0') ? ft_join(&(*dst), tmp, 1) : ft_join(&(*dst), tmp, 0);
	}
}
