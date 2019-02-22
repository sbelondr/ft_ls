/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:49:40 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/22 11:32:39 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		recover_path(char (*path)[BUFF_S], t_ls *ls, int index)
{
	ft_bzero(&(*path), BUFF_S);
	ft_join(&(*path) , ls->options[index], 0);
	((*path)[ft_strlen(*path) - 1] != '/') ? ft_join(&(*path), "/", 0) : 0;
	ft_join(&(*path) , ls->read_file->d_name, 0);
}

void		make_perm(char (*perm)[11], int permissions, int type)
{
	int		i;
	int		j;
	int		stock;
	char	perm_str[BUFF_S];

	i  = 1;
	(*perm)[0] = (type == 8) ? '-' : 'd';
	ft_convert_base(permissions, 8, &perm_str);
	j = ft_strlen(perm_str) - 4;
	while (perm_str[++j])
	{
		stock = perm_str[j] - '0';
		(*perm)[i++] = ((stock - 4) >= 0) ? 'r' : '-';
		(stock - 4) >= 0 ? stock -= 4 : 0;
		(*perm)[i++] = ((stock - 2) >= 0) ? 'w' : '-';
		(stock - 4) >= 0 ? stock -= 2 : 0;
		(*perm)[i++] = ((stock - 1) >= 0) ? 'x' : '-';
	}
	(*perm)[10] = '\0';
}

int			verif_name(char *str, t_ls *ls)
{
	if (!str)
		return (-1);
	if (str[0] && str[0] == '0' && ft_strchr_exist(ls->flags, 'a') == 0)
		return (1);
	return (0);
}

void		split_time(char (*tab)[BUFF_S], char *str)
{
	char	**split;
	char	**split_time;
	int		i;

	split = ft_strsplit(str, ' ');
	ft_bzero(&(*tab), BUFF_S);
	ft_cpy_str(&(*tab), split[1]);
	ft_join(&(*tab), " ", 0);
	ft_join(&(*tab), split[2], 0);
	ft_join(&(*tab), " ", 0);
	split_time = ft_strsplit(split[3], ':');
	ft_join(&(*tab), split_time[0], 0);
	ft_join(&(*tab), ":", 0);
	ft_join(&(*tab), split_time[1], 0);
	i = -1;
	while (split_time[++i])
		ft_strdel(&split_time[i]);
	free(split_time);
	split_time = NULL;
	i = -1;
	while (split[++i])
		ft_strdel(&split[i]);
	free(split);
	split = NULL;
}

void		insert_read(t_ls **ls, int index, t_save **sv)
{
	char	*time_str;
	t_read	*r;

	r = NULL;
	if (verif_name((*ls)->read_file->d_name, (*ls)))
		return ;
	if (!(r = (t_read*)malloc(sizeof(t_read) * 1)))
		return ;
	r->ls = (*ls);
	r->name = (*ls)->read_file->d_name;
	recover_path(&(r)->path, (*ls), index);
	if (stat(r->path, &(r)->file_stat) > 0)
		error_see();
	if ((r->pwuser = getpwuid(r->file_stat.st_uid)) == NULL)
	{
		r->pwuser = 0;
		ft_printf("%s\n", strerror(errno));
	}
	if ((r->grpname = getgrgid(r->file_stat.st_gid)) == NULL)
		error_see();
	make_perm(&(r)->perm, r->file_stat.st_mode, (*ls)->read_file->d_type);
	time_str = ctime(&(r)->file_stat.st_mtime);
	split_time(&(r)->time_last_edit, time_str);
	(*ls)->total += (r->perm[0] == '-') ? (r->file_stat.st_blksize) / 254 : 0;
	insert_sv(&(*sv), r);
}
