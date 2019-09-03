/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_tablo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:08:58 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 10:38:35 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_reverse_tablo(char (*tab)[BUF_S])
{
	char	tmp[BUF_S];
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(*tab) - 1;
	ft_bzero(&tmp, BUF_S);
	while (++i <= len)
		tmp[i] = (*tab)[len - i];
	ft_bzero(&(*tab), BUF_S);
	i = -1;
	while (tmp[++i])
		(*tab)[i] = tmp[i];
}
