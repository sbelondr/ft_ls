/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:13:10 by sbelondr          #+#    #+#             */
/*   Updated: 2018/11/16 10:38:26 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			cpt;
	size_t			result;
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char*)s1;
	d = (unsigned char*)s2;
	cpt = 0;
	result = 0;
	while (s[cpt] && d[cpt] && cpt < n && s[cpt] == d[cpt])
		cpt++;
	if (cpt < n && s[cpt] != d[cpt])
		result = s[cpt] - d[cpt];
	return (result);
}
