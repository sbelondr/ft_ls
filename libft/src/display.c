/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:33:13 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/13 12:36:51 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	ft_display(char dst[BUFF_S], t_printf **lst)
{
	(*lst)->len += ft_strlen(dst);
	ft_putstr(dst);
}
