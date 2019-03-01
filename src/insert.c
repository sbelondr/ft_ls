/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:49:40 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/25 21:05:09 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_ls.h"

void		recover_path(char (*path)[BUFF_S], t_ls *ls, int index)
{
	ft_bzero(&(*path), BUFF_S);
	ft_join(&(*path) , ls->options[index], 0);
	((*path)[ft_strlen(*path) - 1] != '/') ? ft_join(&(*path), "/", 0) : 0;
	ft_join(&(*path) , ls->read_file->d_name, 0);
}

char		type_file(t_ls *ls)
{
	int		type;

	type = ls->read_file->d_type;
	if (type == DT_DIR)
		return ('d');
	else if (type == DT_REG)
		return ('-');
	else if (type == DT_LNK)
		return ('l');
	else if (type == DT_BLK)
		return ('b');
	else if (type == DT_CHR)
		return ('c');
	else if (type == DT_SOCK)
		return ('s');
	else if (type == DT_FIFO)
		return ('p');
	else
		return ('~');
}

void		make_perm(t_read **r, int folder, t_ls *ls)
{
	int		i;

	i  = 1;
	if (folder)
		(*r)->perm[0] = type_file(ls);
	else
		(*r)->perm[0] = '-';
	if ((*r)->perm[0] == 'l')
	{
		(lstat((*r)->path, &(*r)->file_stat) > 0) ? error_see() : 0;
		readlink((*r)->path, (*r)->symbolic_link, BUFF_S);
	}
	else
		ft_bzero(&((*r)->symbolic_link), BUFF_S);
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
	if (c == '-' || c == 'l')
		return (len);
	return (0);
}

/*
 ** a gerer: - major minor
 **			- user ou grp qui n'existe pas (donc chiffre)
 */

void		cnt_column(t_ls **ls, t_read *r)
{
	if (ft_numlen(r->file_stat.st_nlink) > (*ls)->column[1])
		(*ls)->column[1] = ft_numlen(r->file_stat.st_nlink);
	if ((int)ft_strlen(r->pwuser->pw_name) > (*ls)->column[2])
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
	(stat(r->path, &(r)->file_stat) > 0) ? error_see() : 0;
	make_perm(&r, 1, (*ls));
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

	i = 0;
	while (r->perm[i] == '-')
		i++;
	if (i == 10)
		return (0);
	return (1);
}

int			insert_read_file(t_ls **ls, int index)
{
	t_save	*sv;
	char	*time_str;
	t_read	*r;

	r = NULL;
	if (verif_name((*ls)->options[index], (*ls)))
		return (0);
	if (!(r = (t_read*)malloc(sizeof(t_read) * 1)))
		return (0);
	r->ls = (*ls);
	r->name = ft_strdup((*ls)->options[index]);
	if ((stat((*ls)->options[index], &(r)->file_stat)) < 0)
	{
		free(r->name);
		r->name = NULL;
		free(r);
		r = NULL;
		return (0);
	}
	make_perm(&r, 0, (*ls));
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
