/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_tab_fix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:06:57 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/12 13:14:11 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

void	ft_strsub_tab_fix(char (*tab)[BUFF_S], char src[BUFF_S], int start,
		int len)
{
	int	i;

	ft_bzero(*tab, BUFF_S);
	i = -1;
	while (src[start] && ++i < len)
		(*tab)[i] = src[start + i];
}
