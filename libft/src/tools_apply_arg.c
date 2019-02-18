/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_apply_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 11:24:00 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/13 12:37:19 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	verif_p(char (*dst)[BUFF_S], t_printf **lst)
{
	if ((*dst)[0] == '0' && (*dst)[1] == '\0')
	{
		(*dst)[0] = '0';
		(*dst)[1] = 'x';
		(*dst)[2] = '0';
	}
	else if ((*dst)[0] == '0' && (*dst)[1] == 'x' && (*dst)[2] == '\0' &&
			((*lst)->precision > 0 || (*lst)->precision == -2))
	{
		(*dst)[2] = '0';
	}
	if ((*lst)->large_min == 0)
		(*lst)->precision -= 2;
}

int		ft_exception(t_printf *lst)
{
	if (lst->flag == 'd' || lst->flag == 'i' || ft_tolower(lst->flag) == 'x' ||
			ft_tolower(lst->flag) == 'o')
		return (1);
	return (0);
}

void	check_space(t_printf *lst, char (*dst)[BUFF_S])
{
	if (ft_strchr_exist(lst->options, ' ') == 1 && lst->flag == 'd')
		if (lst->large_min > 0)
			ft_startjoin(&(*dst), ' ');
}

void	manage_plus_decimal(char (*dst)[BUFF_S], t_printf *lst, int stock[3])
{
	if (lst->flag == 'd' || lst->flag == 'i')
	{
		if (stock[0] == 1 && ft_strchr_exist(*dst, '-') == 0)
			ft_join(&(*dst), "+", 1);
		if (stock[0] == 0 && ft_strchr_exist(*dst, '-') == 0 &&
				ft_strchr_exist(lst->options, ' ') == 1 &&
				(lst->large_min == 0 || lst->large_min > ft_strlen(*dst)))
			ft_join(&(*dst), " ", 1);
	}
}
