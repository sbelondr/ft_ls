/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deplace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:04:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/12 13:05:43 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

/*
** deplace |0123
**         |00123
*/

void	ft_deplace(char (*tab)[BUFF_S])
{
	int		i;

	i = ft_strlen(*tab);
	while (--i >= 0)
		(*tab)[i + 1] = (*tab)[i];
	(*tab)[0] = '0';
}
