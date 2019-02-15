/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 11:44:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/15 10:57:25 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_read_l(t_read *r)
{
	//ft_printf("ino: %u\n", r->file_stat.st_ino);
	ft_printf("%s", r->perm);
	ft_printf("\t%d", r->file_stat.st_nlink);
	ft_printf("\t%s", r->pwuser->pw_name);
	ft_printf("\t%s", r->grpname->gr_name);
	ft_printf("\t%d", r->file_stat.st_size);
	ft_printf("\t%s", r->time_last_edit);
	ft_printf("\t%s", r->name);
	ft_printf("\n");
}

void	display_normal_mode(t_read *r)
{
	ft_printf("%s\n", r->name);
}

void	display_read(t_ls *ls, t_save *sv)
{
	if (ft_strchr_exist(ls->flags, 'l'))
	{
		ft_printf("total %d\n", ls->total - 1);
		while (sv->list != NULL)
		{
			display_read_l(sv->list);
			sv_next(sv);
		}
	}
	else
	{
		while (sv->list != NULL)
		{
			display_normal_mode(sv->list);
			sv_next(sv);
		}
	}
	if (ft_strchr_exist((ls)->flags, 'R'))
		ft_ls_recursive(sv);
}
