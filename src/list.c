/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:17:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/05 11:26:47 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_ls.h"

t_save		*init_sv(void)
{
	t_save	*sv;
	t_read	*start;

	if (!(sv = (t_save*)malloc(sizeof(t_save) * 1)))
		return (NULL);
	if (!(start = (t_read*)malloc(sizeof(t_read) * 1)))
		return (NULL);
	start->ls = NULL;
	start->name = NULL;
	start->pwuser = NULL;
	start->grpname = NULL;
	ft_bzero(&(start)->path, BUFF_S);
	sv->p_start = start;
	sv->list = NULL;
	return (sv);
}

void		insert_sv(t_save **sv, t_read *r)
{
	if ((*sv)->list == NULL)
	{
		r->next = NULL;
		(*sv)->p_start->next = r;
	}
	else
	{
		r->next = (*sv)->list->next;
		(*sv)->list->next = r;
	}
	(*sv)->list = r;
}

void		next_sv(t_save *sv)
{
	if (sv && sv->list)
		sv->list = sv->list->next;
}

void		first_sv(t_save *sv)
{
	if (sv)
		sv->list = sv->p_start->next;
}

size_t		size_sv(t_save *sv)
{
	size_t	i;

	i = 0;
	if (sv)
	{
		first_sv(sv);
		while (sv->list != NULL)
		{
			i++;
			next_sv(sv);
		}
	}
	return (i);
}
