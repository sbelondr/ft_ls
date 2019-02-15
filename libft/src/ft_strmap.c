/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:24:49 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:21:22 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		cnt;
	char	*str;

	cnt = -1;
	if (s == NULL)
		return (0);
	str = (char*)malloc(sizeof(char) * ft_strlen((char*)s) + 1);
	if (str == NULL || ft_strlen((char*)s) == 0)
		return (0);
	while (s[++cnt])
		str[cnt] = f(s[cnt]);
	str[cnt] = '\0';
	return (str);
}
