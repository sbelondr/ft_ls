/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:07:58 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/15 10:56:33 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sv_insert_r(t_read *r, t_save *sv)
{
	t_read	*r_sv;
	t_read	*r_other;

	if (sv)
	{
		r_other = sv->list;
		r_sv = r;
		if (r_other == NULL)
		{
			sv->p_start->next = r_sv;
			r_sv->next = NULL;
		}
		else
		{
			r_sv->next = r_other->next;
			r_other->next = r_sv;
		}
		sv->list = r_sv;
	}
}

void	sv_remove(t_save *sv)
{
	t_read	*r;
	int		len;
	int		i;

	len = 0;
	r = sv->list;
	sv_first(sv);
	while (sv->list->next != NULL)
	{
		ft_printf("boucle avec moi!\n");
		++len;
		if (ft_strcmp(sv->list->name, r->name))
			break ;
		sv_next(sv);
	}
	sv_first(sv);
	i = -1;
	ft_printf("deb boucle avec moi!\n");
	while (++i != len)
		sv_next(sv);
		ft_printf("fin boucle avec moi!\n");
	sv_remove_next(sv);
}

void	sv_move(t_read *r, t_save *sv)
{
	ft_printf("============ sv_move =============\n");
	t_read	*backup;

	if (!r || !sv)
		return ;
	backup = sv->list;
	sv_remove(sv);
	sv_first(sv);
	display_read(sv->list->ls, sv);
	sleep(1);
	while (sv->list != NULL)
	{
		ft_printf("boucle avec moi!\n");
		if (ft_strcmp(sv->list->name, r->name) == 0)
			break ;
		sv_next(sv);
	}
	ft_printf("============ sv_move > insert_r =============\n");
	sv_insert_r(backup, sv);
	ft_printf("============ sv_move > display_read=============\n");
	display_read(sv->list->ls, sv);
	ft_printf("============ sv_move fin =============\n");
}

void	ft_sort_alph(t_save *sv)
{
	t_read	*r;
	int		i;
	int		len;
	int		stock;

	len = sv_size(sv);
	sv_first(sv);
	i = -1;
	while (++i < len)
	{
		ft_printf("boucle avec moi!\n");
		stock = i;
		ft_printf("deb avec moi!\n");
		while (stock-- > 0)
			sv_next(sv);
		ft_printf("fin avec moi!\n");
		r = sv->list;
		while (sv->list != NULL)
		{
		ft_printf("boucle avec moi!\n");
			if (ft_strcmp(r->name, sv->list->name) > 0)
			{
				ft_printf("av move\n");
				sv_move(r, sv);
				ft_printf("ap move\n");
				break ;
			}
			sv_next(sv);
		}
	}
}

//void	ft_sort_rev(void);

//void	ft_sort_time(void);

void	ft_sort_ls(t_save **sv, t_ls **ls, int index)
{
	if (ft_strchr_exist((*ls)->flags, 't'))
		;//ft_sort_time();
	else
		ft_sort_alph(*sv);
	//	if (ft_strchr_exist((*ls)->flags, 'r'))
	//		ft_sort_rev();
	(void)sv;
	(void)ls;
	(void)index;
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
	}
	free(av);
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
