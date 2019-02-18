/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:07:14 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/18 14:27:25 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_make_permissions(char (*perm)[11], int permissions, int type)
{
	int		i;
	int		j;
	int		stock;
	char	perm_str[BUFF_S];

	i = 1;
	(*perm)[0] = type == 8 ? '-' : 'd';
	ft_convert_base(permissions, 8, &perm_str);
	j = ft_strlen(perm_str) - 4;
	while (perm_str[++j])
	{
		stock = perm_str[j] - '0';
		(*perm)[i++] = ((stock - 4) >= 0) ? 'r' : '-';
		(stock - 4) >= 0 ? stock -= 4 : 0;
		(*perm)[i++] = ((stock - 2) >= 0) ? 'w' : '-';
		(stock - 2) >= 0 ? stock -= 2 : 0;
		(*perm)[i++] = ((stock - 1) == 0) ? 'x' : '-';
	}
	(*perm)[10] = '\0';
}

void	ft_recover_path(char (*path)[1024], t_ls *ls, int index)
{
	ft_bzero(&(*path), 1024);
	ft_join(&(*path), ls->options[index], 0);
	((*path)[ft_strlen(*path) - 1] != '/') ? ft_join(&(*path), "/\0", 0) : 0;
	ft_join(&(*path), ls->read_file->d_name, 0);
}

void	ft_split_time(char (*tab)[BUFF_S], char *str)
{
	char	**split;
	char	**split_time;

	split = ft_strsplit(str, ' ');
	ft_bzero(&(*tab), BUFF_S);
	ft_cpy_str(&(*tab), split[1]);
	ft_join(&(*tab), " \0", 0);
	ft_join(&(*tab), split[2], 0);
	ft_join(&(*tab), " \0", 0);
	split_time = ft_strsplit(split[3], ':');
	ft_join(&(*tab), split_time[0], 0);
	ft_join(&(*tab), ":\0", 0);
	ft_join(&(*tab), split_time[1], 0);
}

/*
** https://nicolasj.developpez.com/articles/listesimple/#LIII-I
*/

t_save	*save_new(void)
{
	t_save	*sv;
	t_read	*deb;

	if (!(sv = (t_save*)malloc(sizeof(t_save) * 1)))
		return (NULL);
	if (!(deb = (t_read*)malloc(sizeof(t_read) * 1)))
		return (NULL);
	deb->ls = NULL;
	deb->name = NULL;
	deb->pwuser = NULL;
	deb->grpname = NULL;
	ft_bzero(&(deb)->path, 1024);
	ft_bzero(&(deb)->time_last_edit, BUFF_S);
	sv->p_start = deb;
	sv->list = NULL;
	return (sv);
}

int		verif_name(char *str, t_ls *ls)
{
	if (!str)
		return (-1);
	if (str && str[0] == '.' && ft_strchr_exist(ls->flags, 'a') == 0)
		return (1);
	return (0);
}

void	insert_lst(t_ls **ls, int index, t_save **sv, t_read *r)
{
	char	*time_str;
	t_read	*old;
/*
	if ((*sv)->list != NULL)
		ft_printf("=dans else first = %s\n", (*sv)->p_start->next->name);
	else
		ft_printf("======= NULL =========\n");
*/	old = (*sv)->list;
	r->ls = (*ls);
	r->name = (*ls)->read_file->d_name;
	ft_recover_path(&(r)->path, (*ls), index);
	if (stat(r->path, &(r)->file_stat) > 0)
	{
		ft_printf("%s", strerror(errno));
		exit(0);
	}
	if ((r->pwuser = getpwuid(r->file_stat.st_uid)) == NULL)
	{
		r->pwuser = 0;
		ft_printf("%s", strerror(errno));
	}
	if ((r->grpname = getgrgid(r->file_stat.st_gid)) == NULL)
	{
		ft_printf("%s", strerror(errno));
		exit(1);
	}
	ft_make_permissions(&(r)->perm, r->file_stat.st_mode,
			(*ls)->read_file->d_type);
	time_str = ctime(&(r)->file_stat.st_mtime);
	ft_split_time(&(r)->time_last_edit, time_str);
	(*ls)->total += (r->perm[0] == '-') ? (r->file_stat.st_blksize) /254 : 0;
	if ((*sv)->list == NULL)
	{
		ft_printf("=+==++=++=====++dans if\n");
		r->next = NULL;
		(*sv)->p_start->next = r;
	}
	else
	{
//		ft_printf("+dans else first = %s r->name = %s\n",
//				(*sv)->p_start->next->name, r->name);
		r->next = (*sv)->list->next;
		(*sv)->list->next = r;
//		ft_printf("-dans else first = %s\n", (*sv)->p_start->next->name);
	}
	(*sv)->list = r;
	ft_printf(">dans else first = %s\n", (*sv)->p_start->next->name);
	//display_read((*ls), sv);
}

void	sv_insert(t_ls **ls, int index, t_save **sv)
{
	if ((*sv)->list != NULL)
		ft_printf("!dans else first = %s\n", (*sv)->p_start->next->name);
	else
		ft_printf("erreur ici\n");
	t_read	*r;

	r = NULL;
	//ft_printf("ls->read_file->d_name = %s\n", (*ls)->read_file->d_name);
	if (verif_name((*ls)->read_file->d_name, (*ls)))
		return ;
	if (!(r = (t_read*)malloc(sizeof(t_read))))
		return ;
	insert_lst(&(*ls), index, &(*sv), r);
	ft_printf("<dans else first = %s\n\n", (*sv)->p_start->next->name);
}

void	sv_next(t_save *sv)
{
	if (sv && sv->list)
		sv->list = sv->list->next;
}

void	sv_first(t_save *sv)
{
	if (sv)
		sv->list = sv->p_start->next;
}

size_t	sv_size(t_save *sv)
{
	size_t	i;

	i = 0;
	if (sv)
	{
		sv_first(sv);
		while (sv->list != NULL)
		{
			i++;
			sv_next(sv);
		}
	}
	return (i);
}

void	sv_remove_next(t_save *sv)
{
	t_read	*a;
	t_read	*b;

	if (sv && sv->list)
	{
		a = sv->list;
		b = NULL;
		b = a->next;
		a->next = b->next;
		free(b);
		b = NULL;
	}
}

void	sv_remove_first(t_save *sv)
{
	if (sv)
	{
		sv->list = sv->p_start;
		sv_remove_next(sv);
	}
}

void	sv_delete(t_save **sv)
{
	if (sv && *sv)
	{
		sv_first(*sv);
		while ((*sv)->list->next != NULL)
			sv_remove_next(*sv);
		sv_remove_first(*sv);
		free((*sv)->list);
		(*sv)->list = NULL;
		free(*sv);
		(*sv) = NULL;
	}
}

int		ft_open_ls(t_ls **ls, int index)
{
	t_save	*sv;

	(*ls)->read_file = NULL;
	(*ls)->rep = opendir((*ls)->options[index]);
	if ((*ls)->rep == NULL)
	{
		ft_printf("%s\n", strerror(errno));
		return (-1);
	}
	sv = save_new();
	while (((*ls)->read_file = readdir((*ls)->rep)) != NULL)
	{
	if ((sv)->list != NULL)
		ft_printf("@dans else first = %s\n", (sv)->p_start->next->name);
	else
		ft_printf("ERREUR");
		if (sv)
			sv_insert(&(*ls), index, &sv);
		else
			ft_printf("erreur peut etre ici\n\n\n");
	}
	ft_printf("sortie\n");
	ft_sort_ls(&sv, &(*ls));
	if (sv)
	{
		sv_first(sv);
		display_read((*ls), sv);
	}
	if ((closedir((*ls)->rep)) == -1)
		exit(-1);
	//sv_delete(&sv);
	return (0);
}
