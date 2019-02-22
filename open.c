/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 10:06:04 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/22 11:04:06 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		open_ls(t_ls **ls, int index)
{
	t_save	*sv;

	(*ls)->rep = opendir((*ls)->options[index]);
	if ((*ls)->rep == NULL)
		error_see();
	sv = init_sv();
	while (((*ls)->read_file = readdir((*ls)->rep)) != NULL)
	{
		if (sv)
			insert_read(&(*ls), index, &sv);
	}
	if (sv)
		display_read((*ls), sv);
	if ((closedir((*ls)->rep)) == -1)
		error_see();
	delete_sv(&sv);
}
