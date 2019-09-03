/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 22:18:24 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:28:16 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	size_t			cnt;
	unsigned char	*str;
	unsigned char	c1;

	str = (unsigned char*)s;
	c1 = (unsigned char)c;
	cnt = -1;
	while (++cnt < n)
		if (str[cnt] == c1)
			return (str + cnt);
	return (0);
}
