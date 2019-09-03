/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:06:04 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/05 21:13:18 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			cmp_racine(char *str)
{
	if (ft_strcmp(str, ".") == 0 || ft_strcmp(str, "..") == 0)
		return (0);
	return (1);
}

void		del_av_str(char ***av, char **str)
{
	if (*av)
	{
		free(*av);
		*av = NULL;
	}
	ft_strdel(&(*str));
}

void		recursive(t_save *sv)
{
	char	**av;
	char	*str;

	first_sv(sv);
	while (sv && sv->list != NULL)
	{
		if (sv->list->perm[0] == 'd' && cmp_racine(sv->list->name))
		{
			ft_printf("\n%s:\n", sv->list->path);
			if (ft_strcmp(sv->list->perm, "d---------") == 0)
				error_permissions(sv->list);
			else
			{
				if (!(av = (char**)malloc(sizeof(char*) * 3)))
					return ;
				str = ft_strjoin("-", sv->list->ls->flags);
				av[0] = str;
				av[1] = str;
				av[2] = sv->list->path;
				ft_ls(3, av);
				del_av_str(&av, &str);
			}
		}
		next_sv(sv);
	}
}

int			choice_insert(t_ls **ls, int index, t_save **sv)
{
	int	cnt;

	cnt = 0;
	(*ls)->total = 0;
	while (((*ls)->read_file = readdir((*ls)->rep)) != NULL)
	{
		if (*sv)
			cnt += insert_read(&(*ls), index, &(*sv));
	}
	if (*sv && cnt > 0)
		display_read((*ls), *sv, 0);
	else if (*sv && cnt == -5)
		display_read((*ls), *sv, -1);
	return (cnt);
}

int			open_ls(t_ls **ls, int index, int see_folder, int first)
{
	t_save	*sv;
	int		cnt;
	int		verif;

	(*ls)->rep = opendir((*ls)->options[index]);
	if ((*ls)->rep == NULL)
	{
		error_rep((*ls)->options[index]);
		return (0);
	}
	if (see_folder)
	{
		(see_folder != 1 && first != 0) ? ft_putchar('\n') : 0;
		ft_printf("%s:\n", (*ls)->options[index]);
	}
	sv = init_sv();
	cnt = choice_insert(&(*ls), index, &sv);
	if ((closedir((*ls)->rep)) == -1)
		error_see();
	(ft_strchr_exist((*ls)->flags, 'R') && cnt > 0) ? recursive(sv) : 0;
	verif = sv->p_start->next != NULL ? 1 : 0;
	delete_sv(&sv, cnt);
	return (verif);
}
