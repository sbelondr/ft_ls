/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:35:21 by sbelondr          #+#    #+#             */
/*   Updated: 2018/11/16 10:41:35 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	cnt;
	int	cnt_n;

	cnt = -1;
	if (*needle == '\0')
		return ((char*)haystack);
	while (haystack[++cnt])
	{
		cnt_n = 0;
		while (needle[cnt_n] && needle[cnt_n] == haystack[cnt + cnt_n])
			cnt_n++;
		if (!needle[cnt_n])
			return ((char*)haystack + cnt);
	}
	return (0);
}
