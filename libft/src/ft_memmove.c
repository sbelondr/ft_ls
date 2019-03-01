/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:53:20 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:27:50 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*s;
	unsigned char		*d;

	s = (const unsigned char*)src;
	d = (unsigned char*)dst;
	if (d > s)
	{
		s += len;
		d += len;
		while (len-- > 0)
			*--d = *--s;
	}
	else
	{
		while (len-- > 0)
			*d++ = *s++;
	}
	return (dst);
}
