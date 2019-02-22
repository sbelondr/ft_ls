/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:11:36 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:23:00 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static int	ft_nb_split(const char *s, char c)
{
	int		cnt;
	int		nb_split;

	cnt = 0;
	nb_split = 0;
	while (s[cnt])
	{
		while (s[cnt] && s[cnt] == c)
			cnt++;
		while (s[cnt] && s[cnt] != c)
			cnt++;
		nb_split++;
		while (s[cnt] && s[cnt] == c)
			cnt++;
	}
	return (nb_split);
}

static char	**ft_split(const char *s, char c, char **result)
{
	int		cnt;
	int		nb_split;
	int		nb_char;

	cnt = 0;
	nb_split = -1;
	while (s[cnt])
	{
		while (s[cnt] && s[cnt] == c)
			cnt++;
		nb_char = 0;
		while (s[cnt + nb_char] && s[cnt + nb_char] != c)
			nb_char++;
		nb_split = (nb_char > 0) ? nb_split + 1 : nb_split;
		if (!(result[nb_split] = ft_strsub(s, cnt, nb_char)))
			return (0);
		cnt += nb_char;
		while (s[cnt] && s[cnt] == c)
			cnt++;
	}
	result[++nb_split] = 0;
	return (result);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**result;

	if (!s)
		return (0);
	if (!(result = (char**)malloc(sizeof(char*) * (ft_nb_split(s, c) + 1))))
		return (0);
	result = ft_split(s, c, result);
	return (result);
}
