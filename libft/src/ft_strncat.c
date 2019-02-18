/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 23:35:47 by sbelondr          #+#    #+#             */
/*   Updated: 2018/11/16 10:37:48 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	cnt_s1;
	size_t	cnt_s2;

	cnt_s1 = 0;
	cnt_s2 = 0;
	while (s1[cnt_s1])
		cnt_s1++;
	while (s2[cnt_s2] && n > cnt_s2)
		s1[cnt_s1++] = s2[cnt_s2++];
	s1[cnt_s1] = '\0';
	return (s1);
}
