/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:07:58 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/16 17:07:05 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sv_move(t_read *r, t_save *sv, t_read *last)
{/*
	sv->list_last->next = r->next;
	r->next = sv->list;
	if (last)
		last->next = r;
	else
		sv->p_start->next = r;
		//sv->p_start->next = r;*/
	(void)r;
	(void)sv;
	(void)last;
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

	while (len-- > 0)
	{
		sv_first(sv);
		last = NULL;
		while (sv->list != NULL)
		{
			r = sv->list;
			sv->list_last = r;
			while (r)
			{
				if (ft_cmp_sort_alph(r->name, sv->list->name, is_r))
				{
					sv_move(r, sv, last);
					break ;
				}
				sv->list_last = r;
				r = r->next;
			}
			last = sv->list;
			sv_next(sv);
		}
	}
}

/*
** https://stackoverflow.com/questions/8304259/formatting-struct-timespec
*/

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
		sv_first(sv);
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
			sv_next(sv);
		}
	}
}

void	ft_sort_ls(t_save **sv, t_ls **ls)
{
	size_t	len;
	int		is_r;

	is_r = (ft_strchr_exist((*ls)->flags, 'r') > 0) ? 1 : 0;
	len = sv_size(*sv);
	if (ft_strchr_exist((*ls)->flags, 't'))
		ft_sort_time(*sv, len, is_r);
	else
		ft_sort_alph(*sv, len, is_r);
}

void	ft_recursive(t_read *r)
{
	char	**av;
	char	flags[BUFF_S];

	ft_bzero(&flags, BUFF_S);
	if (!(av = (char**)malloc(sizeof(char) + 4)))
		return ;
	if (r->perm[0] == 'd' && ft_strcmp(r->name, ".\0") &&
			ft_strcmp(r->name, "..\0"))
	{
		ft_join(&flags, r->ls->flags, 0);
		ft_join(&flags, "-\0", 1);
		ft_printf("%s:\n", r->path);
		av[0] = ft_strdup("./ft_ls\0");
		av[1] = flags;
		av[2] = r->path;
		av[3] = 0;
		ft_ls(3, av);
		ft_printf("\n");
/*		while (*av)
		{
			ft_strdel(&(*av));
			(*av)++;
		}*/
	}
	//free(&av);
}

void	ft_ls_recursive(t_save *sv)
{
	sv_first(sv);
	while (sv->list != NULL)
	{
		ft_recursive(sv->list);
		sv_next(sv);
	}
}
