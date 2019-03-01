/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:07:39 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/25 22:01:26 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_ls.h"

void	error_option(char c)
{
//	ft_printf("ls: illegal option -- %c\n", c);
//	ft_printf("usage: ls [-Ralrt] [file ...]\n");
	ft_dprintf(2, "ls: illegal option -- %c\n", c);
	ft_dprintf(2, "usage: ls [-Ralrt] [file ...]\n");	
	exit(1);
}

void	error_see(void)
{
	ft_dprintf(2, "%s\n", strerror(errno));
}

void	error_permissions(t_read *r)
{
	ft_dprintf(2, "ls: %s: Permission denied\n", r->name);
}

void	error_rep(char *str)
{
	ft_dprintf(2, "ls: %s: %s\n", str, strerror(errno));
}

void	error_file(char *str)
{
	ft_dprintf(2, "ls: %s: No such file or directory\n", str);
	exit(1);
}

void	error_test(int i)
{
	ft_dprintf(2, "Ton ls crash connard: %d\n", i);
	exit(1);
}
