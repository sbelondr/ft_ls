/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 23:59:21 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:19:56 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int				cpt;
	int				result;
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char*)s1;
	d = (unsigned char*)s2;
	cpt = 0;
	result = 0;
	while (s[cpt] && d[cpt] && s[cpt] == d[cpt])
		cpt++;
	if (s[cpt] != d[cpt])
		result = s[cpt] - d[cpt];
	return (result);
}
