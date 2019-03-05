/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 09:07:40 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/05 11:33:54 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_ls.h"

int		verif_flag(t_ls **ls, char *str)
{
	int		i;
	int		len;
	char	*flags;

	flags = ft_strdup("1lRrats");
	i = 0;
	len = ft_strlen((*ls)->flags);
	while (str[++i])
	{
		if (ft_strchr_exist(flags, str[i]))
			(*ls)->flags[len++] = str[i];
		else if (ft_strcmp(str, "--") == 0)
			(*ls)->flags[len++] = str[i];
		else
			error_option(str[i]);
		if (str[i] == '-')
			return (1);
	}
	if (i == 1)
		return (2);
	free(flags);
	flags = NULL;
	return (0);
}

/*
** flags: l -> display.c | R -> recursive.c | a -> list | r, t -> sort.c
*/

int		parser(int ac, char **flags, t_ls **ls)
{
	int		i;
	int		j;
	int		verif;

	i = 0;
	verif = 0;
	while (++i < ac && verif == 0)
	{
		if (flags[i] && flags[i][0] == '-')
			verif = verif_flag(&(*ls), flags[i]);
		else
			break ;
	}
	(verif == 2) ? i-- : 0;
	j = ac - i;
	(j == 0) ? j = 1 : 0;
	if (!((*ls)->options = (char**)malloc((sizeof(char*) * j) + 1)))
		return (-1);
	j = -1;
	if ((ac - i) > 0)
	{
		while (i < ac && flags[i])
			((*ls)->options)[++j] = flags[i++];
	}
	else
	{
		if (!(((*ls)->options)[0] = (char*)malloc(sizeof(char) * 2)))
			return (-1);
		((*ls)->options)[0][0] = '.';
		((*ls)->options)[0][1] = '\0';
	}
	j += 1;
	return (j);
}
