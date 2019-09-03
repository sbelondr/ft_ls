/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrjoin_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 23:13:55 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:23:26 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chrjoin_start(char c, char *str)
{
	char	*dst;
	int		len;
	int		i;

	if (!str || !c)
		return (NULL);
	len = ft_strlen(str) + 1;
	dst = ft_strnew(len);
	if (!dst)
		return (NULL);
	i = 0;
	dst[i] = c;
	while (++i < len)
		dst[i] = str[i - 1];
	dst[i] = '\0';
	return (dst);
}
