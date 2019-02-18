/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:21:48 by sbelondr          #+#    #+#             */
/*   Updated: 2018/11/12 11:47:51 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	cnt;

	if (s && f)
	{
		cnt = -1;
		while (s[++cnt])
			f(cnt, &s[cnt]);
	}
}