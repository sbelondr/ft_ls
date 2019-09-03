/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 23:49:34 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:19:37 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	cpt;

	cpt = -1;
	if (src == dst)
		return (dst);
	while (src[++cpt] && cpt < len)
		dst[cpt] = src[cpt];
	if (cpt < len)
		dst[cpt++] = '\0';
	while (cpt < len)
		dst[cpt++] = '\0';
	return (dst);
}
