/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:03:55 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 20:48:44 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long	nb;
	int		cpt;
	int		negatif;

	nb = 0;
	negatif = 0;
	cpt = 0;
	while (ft_isspace(str[cpt]))
		cpt++;
	if (str[cpt] == '-' || str[cpt] == '+')
		if (str[cpt++] == '-')
			negatif = 1;
	while (str[cpt] && ft_isdigit(str[cpt]))
	{
		nb = (nb * 10) + str[cpt] - '0';
		if (nb < 0)
			return ((negatif == 0) ? -1 : 0);
		cpt++;
	}
	if (nb == 0)
		return (0);
	return (negatif == 1 ? -nb : nb);
}
