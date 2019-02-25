/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 22:38:09 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/22 22:51:59 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sv_move(t_read *r, t_save *sv, t_read *last)
{
	sv->list_last->next = r->next;
	r->next = sv->list;
	if (last)
		last->next = r;
	else
		sv->p_start->next = r;
}

int		ft_cmp_sort_alph(char *str_a, char *str_b, int is_r)
{
	if (is_r == 0)
	{
		if (ft_strcmp(str_a, str_b) < 0)
			return (1);
	}
	else
	{
		if (ft_strcmp(str_a, str_b) > 0)
			return (1);
	}
	return (0);
}

void	ft_sort_alph(t_save *sv, size_t len, int is_r)
{
	t_read	*r;
	t_read	*last;
	int		i;

	while (len-- > 0)
	{
		i = 0;
		first_sv(sv);
		last = NULL;
		while (sv->list != NULL)
		{
			r = sv->list;
			sv->list_last = r;
			while (r)
			{
				if (ft_cmp_sort_alph(r->name, sv->list->name, is_r))
				{
					i++;
					sv_move(r, sv, last);
					break ;
				}
				sv->list_last = r;
				r = r->next;
			}
			last = sv->list;
			next_sv(sv);
		}
		if (i == 0)
			break ;
	}
}

/*
 * ** https://stackoverflow.com/questions/8304259/formatting-struct-timespec
 * */

int		ft_timecmp(t_read *a, t_read *b, int is_r)
{
	struct timespec	tm_a;
	struct timespec	tm_b;

	tm_a = a->file_stat.st_mtimespec;
	tm_b = b->file_stat.st_mtimespec;
	if (is_r == 0)
	{
		if (tm_a.tv_sec > tm_b.tv_sec)
			return (1);
		else if (tm_a.tv_sec == tm_b.tv_sec)
			return (ft_cmp_sort_alph(a->name, b->name, is_r));
	}
	else
	{
		if (tm_a.tv_sec < tm_b.tv_sec)
			return (1);
		else if (tm_a.tv_sec == tm_b.tv_sec)
			return (ft_cmp_sort_alph(a->name, b->name, is_r));
	}
	return (0);
}

void	ft_sort_time(t_save *sv, size_t len, int is_r)
{
	t_read	*r;
	t_read	*last;

	while (len-- > 0)
	{
		first_sv(sv);
		last = NULL;
		while (sv->list != NULL)
		{
			r = sv->list;
			sv->list_last = r;
			while (r)
			{
				if (ft_timecmp(r, sv->list, is_r))
				{
					sv_move(r, sv, last);
					break ;
				}
				sv->list_last = r;
				r = r->next;
			}
			last = sv->list;
			next_sv(sv);
		}
	}
}

void	ft_sort_ls(t_save **sv, t_ls **ls)
{
	size_t	len;
	int		is_r;

	is_r = (ft_strchr_exist((*ls)->flags, 'r') > 0) ? 1 : 0;
	len = size_sv(*sv);
	if (ft_strchr_exist((*ls)->flags, 't'))
		ft_sort_time(*sv, len, is_r);
	else
		ft_sort_alph(*sv, len, is_r);
}
