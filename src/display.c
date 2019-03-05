/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 11:44:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/05 11:27:56 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_ls.h"

void	majmin_read(t_read *r)
{
	int	major;
	int	minor;

	major = major(r->file_stat.st_rdev);
	minor = minor(r->file_stat.st_rdev);
	ft_printf("\t%d, %d", major, minor);
}

void	space_line(int nb_space)
{
	int		i;
	char	buff[nb_space + 1];

	i = -1;
	nb_space++;
	while (++i < nb_space)
		buff[i] = ' ';
	buff[i] = '\0';
	write(1, buff, nb_space);
}

void	display_read_l(t_read *r, int is_s, t_ls *ls)
{
	if (is_s)
	{
		ft_printf("%d", r->file_stat.st_blocks);
		ft_printf("\t%s", r->perm);
	}
	else
		ft_printf("%s", r->perm);
	space_line(ls->column[1] - (ft_numlen(r->file_stat.st_nlink) - 1));
	ft_printf("%d", r->file_stat.st_nlink);
	if (r->pwuser)
		space_line(ls->column[2] - (ft_strlen(r->pwuser->pw_name)));
	if (r->pwuser)
		ft_printf("%s", r->pwuser->pw_name);
	else
		ft_printf("%u", r->file_stat.st_uid);
	space_line(ls->column[3] - ft_strlen(r->grpname->gr_name + 1));
	ft_printf("%s", r->grpname->gr_name);
	space_line(ls->column[4] - (ft_numlen(r->file_stat.st_size) - 1));
	if (r->perm[0] != 'b' && r->perm[0] != 'c')
		ft_printf("%d", r->file_stat.st_size);
	else
		majmin_read(r);
	space_line(ls->column[5] - ft_strlen(r->mois));
	ft_printf("%s", r->mois);
	space_line(ls->column[6] - ft_strlen(r->jour));
	ft_printf("%s", r->jour);
	space_line(ls->column[7] - ft_strlen(r->year_or_hours));
	ft_printf("%s", r->year_or_hours);
	ft_putchar(' ');
	if (r->perm[0] == 'd')
		ft_printf("%s", r->name);//ft_printf("\033[0;36m%s\033[0m", r->name);
	else
		ft_printf("%s", r->name);
	if (r->perm[0] == 'l')
		(r->symbolic_link[0] != '\0') ? ft_printf(" -> %s", r->symbolic_link) : 0;
	ft_printf("\n");
}

void	display_normal_mode(t_read *r, int is_s)
{
	if (is_s)
	{
		ft_printf("%d", r->file_stat.st_blocks);
		ft_printf("\t%s\n", r->name);
	}
	else
	{
		if (r->perm[0] == 'd')
			ft_printf("%s\n", r->name);//ft_printf("\033[0;36m%s\033[0m\n", r->name);
		else
			ft_printf("%s\n", r->name);
	}
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
