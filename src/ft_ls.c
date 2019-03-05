/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 09:21:06 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/05 21:56:33 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_ls.h"

int		init_ls(t_ls **ls)
{
	int	i;

	i = -1;
	if (!((*ls) = (t_ls*)malloc(sizeof(t_ls) * 1)))
		return (-1);
	(*ls)->options = NULL;
	(*ls)->rep = 0;
	ft_bzero(&(*ls)->flags, 10);
	(*ls)->total = 0;
	(*ls)->read_file = 0;
	while (++i < 8)
		(*ls)->column[i] = 0;
	(*ls)->column[0] = 1;
	(*ls)->column[5] = 3;
	return (0);
}

int		remove_ls(t_ls **ls, int len)
{
	t_ls	*tontruc;

	tontruc = *ls;
	if (len == 0)
		free(tontruc->options[0]);
	free(tontruc->options);
	free(*ls);
	return (0);
}

int		parcours(t_ls **ls, int len, int *srt_options, int check)
{
	int	i;
	int	verif;

	verif = 0;
	if (len == 1 && srt_options[0] != -1)
		verif = open_ls(&(*ls), 0, 0, 0);
	else
	{
		i = -1;
		while (++i < len)
		{
			if (srt_options[i] != -1)
				verif = open_ls(&(*ls), srt_options[i], i + 1, check++);
			else
				verif = 0;
		}
	}
	return (verif);
}

int		parcours_sl(t_ls **ls, int len, int *srt_options, int check)
{
	int			i;
	int			end;
	int			index;
	int			verif_stat;
	struct stat	verif;

	i = -1;
	while (++i < len)
	{
		index = srt_options[i];
		if (index != -1)
		{
			verif_stat = lstat((*ls)->options[index], &verif);
			end = ft_strlen((*ls)->options[index]) - 1;
			if (verif_stat >= 0 && (*ls)->options[index][0] == '/' &&
					(*ls)->options[index][end] != '/' && S_ISLNK(verif.st_mode))
			{
				insert_read_sl(&(*ls), index);
				check++;
				srt_options[i] = -1;
			}
		}
	}
	i = parcours(&(*ls), len, srt_options, check);
	return (i);
}

void	ft_dirdel(DIR **check)
{
	closedir(*check);
	(*check) = NULL;
}

int		sort_options_is_exist(t_ls **ls, int index_option)
{
	t_read	*r;
	DIR		*check;

	check = NULL;
	if (index_option != -1 &&
			(check = opendir((*ls)->options[index_option])) == NULL)
	{
		if (!(r = (t_read*)malloc(sizeof(t_read) * 1)))
			return (0);
		if (stat((*ls)->options[index_option], &(r)->file_stat) < 0)
		{
			if (lstat((*ls)->options[index_option], &(r)->file_stat) < 0)
			{
				error_rep((*ls)->options[index_option]);
				free(r);
				r = NULL;
				return (-1);
			}
		}
		free(r);
		r = NULL;
	}
	else if (check != NULL)
		ft_dirdel(&check);
	return (1);
}

int		is_file(t_ls **ls, t_read **r, int *srt_options, int i)
{
	if (!(*r = (t_read*)malloc(sizeof(t_read) * 1)))
		return (0);
	if (stat((*ls)->options[srt_options[i]], &(*r)->file_stat) >= 0 ||
		lstat((*ls)->options[srt_options[i]], &(*r)->file_stat) >= 0)
	{
		insert_read_file(&(*ls), srt_options[i]);
		free(*r);
		*r = NULL;
		return (1);
	}
	free(*r);
	*r = NULL;
	return (0);
}

int		open_file_options(t_ls **ls, int len, int *srt_options)
{
	int		i;
	int		verif;
	t_read	*r;
	DIR		*check;

	i = -1;
	verif = 0;
	while (++i < len)
	{
		if (srt_options[i] != -1 &&
				(check = opendir((*ls)->options[srt_options[i]])) == NULL)
		{
			if (is_file(&(*ls), &r, srt_options, i))
			{
				srt_options[i] = -1;
				verif++;
			}
		}
		else if (srt_options[i] != -1 && check != NULL)
			ft_dirdel(&check);
	}
	verif = parcours_sl(&(*ls), len, srt_options, verif);
	return (verif);
}

int		sort_alph(char *path_a, char *path_b)
{
	int	result;

	result = ft_strcmp(path_a, path_b);
	if (result > 0)
		return (1);
	return (0);
}

int		sort_t(struct stat info_a, struct stat info_b)
{
	struct timespec	tm_a;
	struct timespec	tm_b;

	tm_a = info_a.st_mtimespec;
	tm_b = info_b.st_mtimespec;
	if (tm_a.tv_sec < tm_b.tv_sec)
		return (1);
	if (tm_a.tv_sec == tm_b.tv_sec)
		return (-1);
	return (0);
}

int		info_search(char *path_a, char *path_b, t_ls *ls)
{
	int			verif;
	struct stat	info;
	struct stat	info_b;

	verif = -1;
	(stat(path_a, &info) == -1) ? verif = -2 : 0;
	if (stat(path_b, &info_b) == -1)
		verif = -2;
	if (verif == -1 && (S_ISREG(info.st_mode) || S_ISREG(info_b.st_mode)))
	{
		if (S_ISREG(info.st_mode) && S_ISDIR(info_b.st_mode))
			verif = 0;
		if (S_ISREG(info_b.st_mode) && S_ISDIR(info.st_mode))
			verif = 1;
	}
	if (verif == -1 || verif == -2)
	{
		if (verif == -1 && ft_strchr_exist(ls->flags, 't'))
			verif = sort_t(info, info_b);
		if (verif == -1 || verif == -2)
			verif = sort_alph(path_a, path_b);
	}
	if (ft_strchr_exist(ls->flags, 'r'))
		verif = (verif == 0) ? 1 : 0;
	return (verif);
}

/*
** http://manpagesfr.free.fr/man/man2/stat.2.html
*/

int		sort_options(t_ls **ls, int len, int *srt_options)
{
	int		i;
	int		k;
	int		stock;

	k = -1;
	while (++k < len)
	{
		i = -1;
		while (++i < len - 1)
		{
			if (srt_options[i] != -1)
			{
				if (srt_options[i + 1] == -1 ||
						info_search((*ls)->options[srt_options[i]],
							(*ls)->options[srt_options[i + 1]], (*ls)))
				{
					stock = srt_options[i];
					srt_options[i] = srt_options[i + 1];
					srt_options[i + 1] = stock;
				}
			}
		}
	}
	stock = open_file_options(&(*ls), len, srt_options);
	return (stock);
}

int		first_sort_options(t_ls **ls, int len, int *srt_options)
{
	int	i;
	int	k;
	int	stock;

	k = -1;
	while (++k < len)
	{
		i = -1;
		while (++i < len - 1)
		{
			if (ft_strcmp((*ls)->options[srt_options[i]],
						(*ls)->options[srt_options[i + 1]]) > 0)
			{
				stock = srt_options[i];
				srt_options[i] = srt_options[i + 1];
				srt_options[i + 1] = stock;
			}
		}
	}
	i = -1;
	while (++i < len)
		if (sort_options_is_exist(&(*ls), srt_options[i]) == -1)
			srt_options[i] = -1;
	stock = sort_options(&(*ls), len, srt_options);
	return (stock);
}

int		init_srt_options(t_ls **ls, int len)
{
	int		srt_options[len];
	int		i;
	int		stock;

	i = -1;
	while (++i < len)
		srt_options[i] = i;
	stock = first_sort_options(&(*ls), len, srt_options);
	return (stock);
}

int		ft_ls(int ac, char **av)
{
	t_ls	*ls;
	int		len;
	int		check;
	int		verif;

	verif = 0;
	if (!av)
		return (-1);
	if (init_ls(&ls) == -1)
		return (-1);
	len = parser(ac, av, &ls);
	check = (len < 1) ? 1 : len;
	verif = init_srt_options(&ls, check);
	if (remove_ls(&ls, len) == -1)
		return (-1);
	return (verif);
}
