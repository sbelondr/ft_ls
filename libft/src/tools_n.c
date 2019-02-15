/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_n.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 13:25:31 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/13 12:37:45 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	ft_precision_u_correct(t_printf **lst, char *str)
{
	if ((*lst)->precision == -1 && ft_strchr_exist((*lst)->options, '0'))
		(*lst)->options[ft_chr_index((*lst)->options, '0')] = ' ';
	if ((*lst)->precision == 0 && str[0] != '\0')
		(*lst)->precision = -2;
}

int		ft_verif_space_n(t_printf **lst, char *str)
{
	int	verif;

	if (str && str[0] == '-' && (*lst)->large_min > 0)
		verif = 1;
	else
		verif = 0;
	if (ft_strchr_exist((*lst)->options, ' ') && (*lst)->large_min > 0 &&
			(ft_strlen(str) < (*lst)->large_min || verif == 1))
		return (1);
	return (0);
}

void	ft_affiche_n_null(t_printf **lst)
{
	char	str[BUFF_S];
	int		stock[3];

	ft_bzero(&str, BUFF_S);
	if (ft_strchr_exist((*lst)->options, '+'))
	{
		str[0] = '+';
		((*lst)->large_min > 0) ? (*lst)->large_min += 1 : 0;
	}
	ft_stock(&(*lst), str, &stock);
	ft_large_min(&str, (*lst), stock);
	ft_display(str, &(*lst));
}

/*
**	example :
**		deb->"  bbbbbAflkdkf"
**		fin->"  Abbbbbflkdkf"
*/

void	ft_correct(char (*dst)[BUFF_S], char a, char b, t_printf **lst)
{
	int	index[2];
	int	i;
	int	len;

	index[0] = ft_chr_index((*dst), a);
	index[1] = ft_chr_index((*dst), b);
	if (index[0] != -1 && index[1] != -1 && index[0] > index[1])
	{
		(*dst)[index[0]] = b;
		(*dst)[index[1]] = a;
	}
	i = -1;
	while ((*dst)[++i])
		if ((*dst)[i] != ' ')
			break ;
	len = ft_strlen(*dst) - 1;
	if (len == i && (*dst)[i] == '0' && (*lst)->large_min > 0 &&
			ft_strchr_exist((*lst)->options, '#') == 0)
		(*dst)[i] = ' ';
	len = ft_strlen(*dst) - 1;
	if ((*lst)->large_min > 0 && len == i &&
			ft_strchr_exist((*lst)->options, '#') == 0)
		(*dst)[i] = '0';
	if ((*lst)->large_min > 0 && (*lst)->precision == 0 && len == i)
		(*dst)[i] = ' ';
}
