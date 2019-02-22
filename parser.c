/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 09:07:40 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/22 09:59:37 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		verif_flag(t_ls **ls, char *str)
{
	int	i;
	int	len;
	static char	*flags;

	if (!flags)
		flags = ft_strdup("1lRrat");
	i = 0;
	len  = ft_strlen((*ls)->flags);
	(len > 0) ? len -= 1 : 0;
	while (str[++i])
	{
		if (ft_strchr_exist(flags, str[i]))
			(*ls)->flags[len++] = str[i];
		else
			error_option(str[i]);
	}
	return (0);
}

/*
** flags: l -> display.c | R -> recursive.c | a -> list | r, t -> sort.c
*/

int		parser(int ac, char **flags, t_ls **ls)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		if (flags[i] && flags[i][0] == '-')
			verif_flag(&(*ls), flags[i]);
		else
			break ;
	}
	if (!((*ls)->options = (char**)malloc(sizeof(char*) + (ac - i + 1))))
		return (-1);
	j = 0;
	while (i < ac)
		(*ls)->options[j++] = ft_strdup(flags[i++]);
	if (j == 0)
		(*ls)->options[j++] = ft_strdup(".\0");
	return (j);
}
