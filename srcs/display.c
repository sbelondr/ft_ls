/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 11:44:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/05 23:16:22 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/sysmacros.h>

int		majmin_read(t_read *r)
{
	int	major;
	int	minor;
	int	cnt;

	major = major(r->file_stat.st_rdev);
	minor = minor(r->file_stat.st_rdev);
	cnt = ft_numlen(major) + ft_numlen(minor) + 2;
	ft_printf("%d, %d", major, minor);
	return (cnt);
}

void	space_line(int nb_space)
{
	int		i;
	char	buff[nb_space + 1];

	i = -1;
	nb_space++;
	ft_bzero(buff, nb_space);
	while (++i < nb_space)
		buff[i] = 32;
	buff[i] = '\0';
	ft_putstr(buff);
}

void	verif_space_line(int nb_space)
{
	if (nb_space < 1)
		space_line(0);
	else
		space_line(nb_space);
}

void	display_user(t_read *r, t_ls *ls)
{
	char	*str;

	if (r->pwuser)
	{
		str = ft_strdup(r->pwuser->pw_name);
		ft_putstr(str);
		verif_space_line(ls->column[2] - (int)ft_strlen(str));
		ft_strdel(&str);
	}
	else
	{
		ft_printf("%u", r->file_stat.st_uid);
		verif_space_line(ls->column[2] - ft_numlen(r->file_stat.st_uid));
	}
}

void	display_size(t_read *r, t_ls *ls)
{
	int	len;
	if (r->perm[0] != 'b' && r->perm[0] != 'c')
	{
		ft_putnbr(r->file_stat.st_size);
		verif_space_line(ls->column[4] - ft_numlen(r->file_stat.st_size));
	}
	else
	{
		len = majmin_read(r);
		verif_space_line(ls->column[4] - len);
	}
}

void	display_name(t_read *r)
{
	if (r->perm[0] == 'd')
		ft_putstr(r->name);
	else
		ft_putstr(r->name);
	if (r->perm[0] == 'l')
		if (r->symbolic_link[0] != '\0')
			ft_printf(" -> %s", r->symbolic_link);
}

void	display_read_l(t_read *r, int is_s, t_ls *ls)
{
	char	*str;

	if (is_s)
		ft_printf("%d\t", r->file_stat.st_blocks);
	ft_putstr(r->perm);
	ft_putchar(' ');
	verif_space_line(ls->column[1] - ft_numlen(r->file_stat.st_nlink));
	ft_putnbr(r->file_stat.st_nlink);
	ft_putchar(' ');
	display_user(r, ls);
	str = ft_strdup(r->grpname->gr_name);
	ft_putstr(str);
	verif_space_line(ls->column[3] - (int)ft_strlen(str));
	ft_strdel(&str);
	display_size(r, ls);
	verif_space_line(ls->column[5] - ft_strlen(r->mois));
	ft_putstr(r->mois);
	verif_space_line(ls->column[6] - ft_strlen(r->jour));
	ft_putstr(r->jour);
	verif_space_line(ls->column[7] - ft_strlen(r->year_or_hours));
	ft_putstr(r->year_or_hours);
	ft_putchar(' ');
	display_name(r);
	ft_putchar('\n');
}

void	display_normal_mode(t_read *r, int is_s)
{
	if (is_s)
		ft_printf("%d\t", r->file_stat.st_blocks);
	ft_printf("%s\n", r->name);
}

void	display_read(t_ls *ls, t_save *sv, int break_line)
{
	int	is_s;

	is_s = ft_strchr_exist(ls->flags, 's');
	ft_sort_ls(&sv, &ls);
	first_sv(sv);
	if (ft_strchr_exist(ls->flags, 'l'))
	{
		(break_line != -1) ? ft_printf("total %d\n", ls->total) : 0;
		while (sv->list != NULL)
		{
			display_read_l(sv->list, is_s, ls);
			next_sv(sv);
		}
	}
	else
	{
		while (sv->list != NULL)
		{
			display_normal_mode(sv->list, is_s);
			next_sv(sv);
		}
	}
}
