/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:31:25 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:22:43 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../headers/libft.h"

static int	ft_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	int		cnt;
	int		i;
	int		last;
	char	*str;

	cnt = -1;
	last = -1;
	i = 0;
	if (!s)
		return (0);
	while (s[++cnt] && ft_white_space(s[cnt]) == 1)
		i++;
	while (s[++cnt])
		if (ft_white_space(s[cnt]) == 0)
			last = cnt;
	if (!(str = (char*)malloc(sizeof(char) * (cnt - (cnt - last - 1) - i + 1))))
		return (0);
	cnt = i;
	i = 0;
	while (s[cnt] && cnt <= last)
		str[i++] = s[cnt++];
	str[i] = '\0';
	return (str);
}
