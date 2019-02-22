/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:52:38 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/22 11:30:14 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		remove_next_sv(t_save *sv)
{
	t_read	*a;
	t_read	*b;

	if (sv && sv->list)
	{
		a = sv->list;
		b = NULL;
		b = a->next;
		a->next = b->next;
		free(b);
		b = NULL;
	}
}

void		remove_first_sv(t_save *sv)
{
	if (sv)
	{
		sv->list = sv->p_start;
		remove_next_sv(sv);
	}
}

void		delete_sv(t_save **sv)
{
	if (sv && *sv)
	{
		first_sv(*sv);
		while ((*sv)->list->next != NULL)
			remove_next_sv(*sv);
		remove_first_sv(*sv);
		free((*sv)->list);
		(*sv)->list = NULL;
		free(*sv);
		(*sv) = NULL;
	}
}
