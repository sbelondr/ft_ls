/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:04:37 by sbelondr          #+#    #+#             */
/*   Updated: 2018/11/16 10:39:44 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	cnt;
	size_t	cnt_n;

	cnt = -1;
	if (*needle == '\0')
		return ((char*)haystack);
	while (haystack[++cnt] && cnt < len)
	{
		cnt_n = -1;
		while (needle[++cnt_n] && needle[cnt_n] == haystack[cnt + cnt_n])
			if (cnt + cnt_n >= len)
				break ;
		if (!needle[cnt_n])
			return ((char*)haystack + cnt);
	}
	return (0);
}
