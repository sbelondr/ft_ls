/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:41:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/16 10:46:45 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		verif_flag(t_ls **ls, char *str)
{
	int			i;
	int			len_flags;
	static char	*flags_ok;

	if (!flags_ok)
		flags_ok = "1lRrat\0";
	i = 0;
	len_flags = ft_strlen((*ls)->flags);
	(len_flags > 0) ? len_flags -= 1 : 0;
	while (str[++i])
	{
		if (ft_strchr_exist(flags_ok, str[i]))
			(*ls)->flags[len_flags++] = str[i];
		else
			error_option(str[i]);
	}
	return (0);
}

/*
** flags: | l -> display.c | | R a -> see.c| | r t -> sort.c|
*/

int		parser(int av, char **flags, t_ls **ls)
{
	int	i;
	int	j;

	i = 0;
	while (++i < av)
	{
		if (flags[i] && flags[i][0] == '-')
			verif_flag(&(*ls), flags[i]);
		else
			break ;
	}
	if (!((*ls)->options = (char**)malloc(sizeof(char*) + av - i + 1)))
		return (-1);
	j = 0;
	while (i < av)
		(*ls)->options[j++] = flags[i++];
	(j == 0) ? (*ls)->options[j++] = ".\0" : 0;
//	(*ls)->options[j] = 0;
	return (j);
}

int		ft_blank_ls(t_ls **ls)
{
	if (!((*ls) = (t_ls*)malloc(sizeof(t_ls) * 1)))
		return (-1);
	ft_bzero(&(*ls)->flags, 10);
	(*ls)->rep = NULL;
	(*ls)->read_file = NULL;
	(*ls)->total = 0;
	return (0);
}

int		ft_parcours(t_ls **ls, int len)
{
	int	i;

	i = 0;
	if (len == 1)
		ft_open_ls(&(*ls), 0);
	else
	{
		while ((*ls)->options[i] && i < len)
		{
			ft_printf("%s:\n", (*ls)->options[i]);
			ft_open_ls(&(*ls), i++);
			(i < len) ? ft_printf("\n") : 0;
		}
	}
	return (0);
}

int		ft_ls(int ac, char **av)
{
	t_ls	*ls;
	int		len;

	ft_blank_ls(&ls);
	len = parser(ac, av, &ls);
	ft_parcours(&ls, len);
	// del ls
	return (0);
}

int		main(int argc, char **argv)
{
	ft_ls(argc, argv);
	return (0);
}
