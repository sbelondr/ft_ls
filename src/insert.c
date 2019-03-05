/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:49:40 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/05 21:56:29 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_ls.h"

void		recover_path(char (*path)[BUFF_S], t_ls *ls, int index)
{
	ft_bzero(&(*path), BUFF_S);
	ft_join(&(*path), ls->options[index], 0);
	((*path)[ft_strlen(*path) - 1] != '/') ? ft_join(&(*path), "/", 0) : 0;
	ft_join(&(*path), ls->read_file->d_name, 0);
}

char		type_file(t_read *r)
{
	if (S_ISREG(r->file_stat.st_mode))
		return ('-');
	else if (S_ISDIR(r->file_stat.st_mode))
		return ('d');
	else if (S_ISLNK(r->file_stat.st_mode))
		return ('l');
	else if (S_ISBLK(r->file_stat.st_mode))
		return ('b');
	else if (S_ISCHR(r->file_stat.st_mode))
		return ('c');
	else if (S_ISSOCK(r->file_stat.st_mode))
		return ('s');
	else if (S_ISFIFO(r->file_stat.st_mode))
		return ('p');
	else
		return ('~');
}

void		make_other_perm(t_read **r)
{
	int	i;
	int	min;

	i = 0;
	min = 0;
	while ((*r)->perm[++i])
		if ((*r)->perm[i] != '-')
		{
			min = 1;
			break ;
		}
	if (S_ISVTX & (*r)->file_stat.st_mode)
		(*r)->perm[9] = (min) ? 't' : 'T';
	if (S_ISGID & (*r)->file_stat.st_mode)
		(*r)->perm[6] = (min) ? 's' : 'S';
	if (S_ISUID & (*r)->file_stat.st_mode)
		(*r)->perm[3] = (min) ? 's' : 'S';
}

void		make_perm(t_read **r, t_ls *ls)
{
	int		i;
	int		verif;

	i = 1;
	ft_bzero(&((*r)->symbolic_link), BUFF_S);
	if ((ls->read_file && ls->read_file->d_type == DT_LNK) ||
			S_ISLNK((*r)->file_stat.st_mode))
	{
		(lstat((*r)->path, &(*r)->file_stat)) > 0 ? error_see() : 0;
		verif = readlink((*r)->path, (*r)->symbolic_link, BUFF_S);
		if (verif < 0)
			readlink((*r)->name, (*r)->symbolic_link, BUFF_S);
	}
	(*r)->perm[0] = type_file(*r);
	(*r)->perm[i++] = S_IRUSR & (*r)->file_stat.st_mode ? 'r' : '-';
	(*r)->perm[i++] = S_IWUSR & (*r)->file_stat.st_mode ? 'w' : '-';
	(*r)->perm[i++] = S_IXUSR & (*r)->file_stat.st_mode ? 'x' : '-';
	(*r)->perm[i++] = S_IRGRP & (*r)->file_stat.st_mode ? 'r' : '-';
	(*r)->perm[i++] = S_IWGRP & (*r)->file_stat.st_mode ? 'w' : '-';
	(*r)->perm[i++] = S_IXGRP & (*r)->file_stat.st_mode ? 'x' : '-';
	(*r)->perm[i++] = S_IROTH & (*r)->file_stat.st_mode ? 'r' : '-';
	(*r)->perm[i++] = S_IWOTH & (*r)->file_stat.st_mode ? 'w' : '-';
	(*r)->perm[i++] = S_IXOTH & (*r)->file_stat.st_mode ? 'x' : '-';
	(*r)->perm[10] = '\0';
	make_other_perm(&(*r));
}

int			verif_name(char *str, t_ls *ls)
{
	if (!str)
		return (-1);
	if (str[0] && str[0] == '.' && ft_strchr_exist(ls->flags, 'a') == 0)
		return (1);
	return (0);
}

void		hour_or_year(char **split, t_read **r)
{
	char	**split_time;
	time_t	t;
	int		i;
	int		verif;

	t = time(NULL);
	verif = ((t - (*r)->file_stat.st_mtime) < 15768000) ? 1 : 0;
	((t - (*r)->file_stat.st_mtime) < 0) ? verif = 0 : 0;
	if (verif == 1)
	{
		split_time = ft_strsplit(split[3], ':');
		ft_cpy_str(&(*r)->year_or_hours, split_time[0]);
		ft_join(&(*r)->year_or_hours, ":", 0);
		ft_join(&(*r)->year_or_hours, split_time[1], 0);
	}
	else
	{
		split_time = ft_strsplit(split[4], '\n');
		ft_cpy_str(&(*r)->year_or_hours, split_time[0]);
	}
	i = -1;
	while (split_time[++i])
		ft_strdel(&split_time[i]);
	free(split_time);
	split_time = NULL;
}

void		split_time(char *str, t_read **r)
{
	char	**split;
	int		i;

	split = ft_strsplit(str, ' ');
	ft_cpy_str(&(*r)->mois, split[1]);
	ft_cpy_str(&(*r)->jour, split[2]);
	hour_or_year(split, &(*r));
	i = -1;
	while (split[++i])
		ft_strdel(&split[i]);
	free(split);
	split = NULL;
}

long long	add_total(t_read **r)
{
	char		c;
	long long	len;

	c = (*r)->perm[0];
	len = (*r)->file_stat.st_blocks;
	return (len);
}

void		cnt_column(t_ls **ls, t_read *r)
{
	if (ft_numlen(r->file_stat.st_nlink) > (*ls)->column[1])
		(*ls)->column[1] = ft_numlen(r->file_stat.st_nlink);
	if (r->pwuser && (int)ft_strlen(r->pwuser->pw_name) > (*ls)->column[2])
		(*ls)->column[2] = ft_strlen(r->pwuser->pw_name);
	if ((int)ft_strlen(r->grpname->gr_name) > (*ls)->column[3])
		(*ls)->column[3] = ft_strlen(r->grpname->gr_name);
	if (ft_numlen(r->file_stat.st_size) > (*ls)->column[4])
		(*ls)->column[4] = ft_numlen(r->file_stat.st_size);
	if ((int)ft_strlen(r->jour) > (*ls)->column[6])
		(*ls)->column[6] = ft_strlen(r->jour);
	if ((int)ft_strlen(r->year_or_hours) > (*ls)->column[7])
		(*ls)->column[7] = ft_strlen(r->year_or_hours);
}

int			insert_read(t_ls **ls, int index, t_save **sv)
{
	char	*time_str;
	t_read	*r;

	r = NULL;
	if (verif_name((*ls)->read_file->d_name, (*ls)))
		return (0);
	if (!(r = (t_read*)malloc(sizeof(t_read) * 1)))
		return (0);
	r->ls = (*ls);
	r->name = ft_strdup((*ls)->read_file->d_name);
	recover_path(&(r)->path, (*ls), index);
	if (stat(r->path, &(r)->file_stat) > 0)
		error_see();
	make_perm(&r, (*ls));
	if ((r->pwuser = getpwuid(r->file_stat.st_uid)) == NULL)
		r->pwuser = 0;
	((r->grpname = getgrgid(r->file_stat.st_gid)) == NULL) ? error_see() : 0;
	time_str = ctime(&(r)->file_stat.st_mtime);
	split_time(time_str, &r);
	(*ls)->total += add_total(&r);
	insert_sv(&(*sv), r);
	cnt_column(&(*ls), r);
	return (1);
}

int			check_permission(t_read *r)
{
	int		i;

	i = 1;
	while (r->perm[i] == '-')
		i++;
	if (i == 10)
		return (0);
	return (1);
}

int			insert_read_sl(t_ls **ls, int index)
{
	t_save	*sv;
	char	*time_str;
	t_read	*r;

	r = NULL;
	if (verif_name((*ls)->options[index], (*ls)) ||
			!(r = (t_read*)malloc(sizeof(t_read) * 1)))
		return (0);
	r->ls = (*ls);
	r->name = ft_strdup((*ls)->options[index]);
	ft_cpy_str(&(r->path), r->name);
	(lstat(r->name, &(r)->file_stat) > 0) ? error_see() : 0;
	make_perm(&r, (*ls));
	if ((r->pwuser = getpwuid(r->file_stat.st_uid)) == NULL)
		r->pwuser = 0;
	((r->grpname = getgrgid(r->file_stat.st_gid)) == NULL) ? error_see() : 0;
	time_str = ctime(&(r)->file_stat.st_mtime);
	split_time(time_str, &r);
	(*ls)->total += add_total(&r);
	sv = init_sv();
	insert_sv(&sv, r);
	check_permission(r) ? display_read((*ls), sv, -1) : error_permissions(r);
	delete_sv(&sv, 1);
	//ft_putchar('\n');
	return (1);
}

int			access_stat(t_ls **ls, t_read **r, int index)
{
	if ((stat((*ls)->options[index], &(*r)->file_stat)) < 0 &&
			lstat((*ls)->options[index], &(*r)->file_stat) < 0)
	{
		free((*r)->name);
		(*r)->name = NULL;
		free(*r);
		*r = NULL;
		return (1);
	}
	return (0);
}

int			insert_read_file(t_ls **ls, int index)
{
	t_save	*sv;
	char	*time_str;
	t_read	*r;

	r = NULL;
	if (verif_name((*ls)->options[index], (*ls)) ||
			!(r = (t_read*)malloc(sizeof(t_read) * 1)))
		return (0);
	r->ls = (*ls);
	r->name = ft_strdup((*ls)->options[index]);
	if (access_stat(&(*ls), &r, index))
		return (0);
	make_perm(&r, (*ls));
	if ((r->pwuser = getpwuid(r->file_stat.st_uid)) == NULL)
		r->pwuser = 0;
	((r->grpname = getgrgid(r->file_stat.st_gid)) == NULL) ? error_see() : 0;
	time_str = ctime(&(r)->file_stat.st_mtime);
	split_time(time_str, &r);
	(*ls)->total += add_total(&r);
	sv = init_sv();
	insert_sv(&sv, r);
	cnt_column(&(*ls), r);
	check_permission(r) ? display_read((*ls), sv, -1) : error_permissions(r);
	delete_sv(&sv, 1);
	return (1);
}
