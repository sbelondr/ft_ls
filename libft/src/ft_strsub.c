/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:54:05 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:22:12 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	cnt;

	cnt = 0;
	if (!s)
		return (0);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (s[start] && len > 0)
	{
		str[cnt] = s[start++];
		len--;
		cnt++;
	}
	str[cnt] = '\0';
	return (str);
}
