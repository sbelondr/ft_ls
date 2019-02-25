/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 09:21:06 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/25 22:08:25 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
			verif = (srt_options[i] != -1) ?
				open_ls(&(*ls), srt_options[i], i + 1, check++) : 0;
		}
	}
	return (verif);
}


int			sort_options_is_exist(t_ls **ls, int len, int *srt_options)
{
	int		i;
	t_read	*r;
	int		verif;
	DIR		*check;

	i = -1;
	while (++i < len)
	{
		if (srt_options[i] != -1 &&
				(check = opendir((*ls)->options[srt_options[i]])) == NULL)
		{
			if (!(r = (t_read*)malloc(sizeof(t_read) * 1)))
				break ;
			if (stat((*ls)->options[srt_options[i]], &(r)->file_stat) < 0)
			{
				error_rep((*ls)->options[srt_options[i]]);
				srt_options[i] = -1;
			}
			free(r);
			r = NULL;
		}
		else if (check != NULL)
		{
			closedir(check);
			check = NULL;
		}
	}
	i = -1;
	verif = 0;
	while (++i < len)
	{
		if (srt_options[i] != -1 &&
				(check = opendir((*ls)->options[srt_options[i]])) == NULL)
		{
			if (!(r = (t_read*)malloc(sizeof(t_read) * 1)))
				break ;
			if (stat((*ls)->options[srt_options[i]], &(r)->file_stat) >= 0)
			{
				insert_read_file(&(*ls), srt_options[i]);
				srt_options[i] = -1;
				verif++;
			}
			free(r);
			r = NULL;
		}
		else if (check != NULL)
		{
			closedir(check);
			check = NULL;
		}
	}
	verif = parcours(&(*ls), len, srt_options, verif);
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
	if (stat(path_a, &info) == -1)
		verif = -2;
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

int		sort_options(t_ls **ls, int len)
{
	int		srt_options[len];
	int		i;
	int		j;
	int		k;
	int		stock;

	i = -1;
	while (++i < len)
		srt_options[i] = i;
	k = -1;
	while (++k < len)
	{
		i = -1;
		while (++i < len)
		{
			j = i;
			while (++j < len)
			{
				if (info_search((*ls)->options[i],
							(*ls)->options[srt_options[j]], (*ls)))
				{
					stock = srt_options[i];
					srt_options[i] = srt_options[j];
					srt_options[j] = stock;
				}
			}
		}
	}
	stock = sort_options_is_exist(&(*ls), len, srt_options);
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
	verif = sort_options(&ls, check);
	if (remove_ls(&ls, len) == -1)
		return (-1);
	return (verif);
}
