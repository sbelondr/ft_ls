/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_exist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 00:37:56 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/26 10:00:49 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				ft_strchr_exist(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (1);
	return (0);
}
