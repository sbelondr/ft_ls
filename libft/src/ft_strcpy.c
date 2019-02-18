/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 23:40:48 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:19:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int	cpt;

	cpt = -1;
	while (src[++cpt])
		dst[cpt] = src[cpt];
	dst[cpt] = '\0';
	return (dst);
}
