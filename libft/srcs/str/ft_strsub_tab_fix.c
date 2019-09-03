/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_tab_fix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:06:57 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/07 10:39:01 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strsub_tab_fix(char (*tab)[BUF_S], char src[BUF_S], int start,
		int len)
{
	int	i;

	ft_bzero(*tab, BUF_S);
	i = -1;
	while (src[start] && ++i < len)
		(*tab)[i] = src[start + i];
}
