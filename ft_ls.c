/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 09:21:06 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/22 10:08:27 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		init_ls(t_ls **ls)
{
	if (!((*ls) = (t_ls*)malloc(sizeof(t_ls) * 1)))
		return (-1);
	(*ls)->options = NULL;
	(*ls)->rep = 0;
	ft_bzero(&(*ls)->flags, 10);
	(*ls)->total = 0;
	(*ls)->read_file = 0;
	return (0);
}

int		remove_ls(t_ls **ls, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		free((*ls)->options[i]);
		(*ls)->options[i] = NULL;
	}
	free((*ls)->options);
	(*ls)->options = NULL;
	free(*ls);
	(*ls) = NULL;
	return (0);
}

void	parcours(t_ls **ls, int len)
{
	int	i;

	if (len == 1)
		open_ls(&(*ls), 0);
	else
	{
		i = 0;
		while (i < len)
		{
			ft_printf("%s:\n", (*ls)->options[i]);
			open_ls(&(*ls), i++);
			if (i < len - 1)
				ft_printf("\n");
		}
	}
}

int		ft_ls(int ac, char **av)
{
	t_ls	*ls;
	int		len;

	if (init_ls(&ls) == -1)
		return (-1);
	len = parser(ac, av, &ls);
	parcours(&ls, len);
	if (remove_ls(&ls, len) == -1)
		return (-1);
	return (0);
}
