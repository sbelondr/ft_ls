/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 23:42:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:20:25 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	cnt_src;
	size_t	size_dst;
	size_t	size_src;

	cnt_src = -1;
	size_dst = ft_strlen((char*)dst);
	size_src = ft_strlen((char*)src);
	if (size <= size_dst)
		return (size_src + size);
	while (src[++cnt_src] && (cnt_src + size_dst) < (size - 1))
		dst[size_dst + cnt_src] = src[cnt_src];
	dst[size_dst + cnt_src] = '\0';
	return (size_dst + size_src);
}
