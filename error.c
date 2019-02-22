/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:07:39 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/22 10:29:10 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_option(char c)
{
	ft_printf("ls: illegal option -- %c\n", c);
	ft_printf("usage: ls [-Ralrt] [file ...]\n");
	exit(1);
}

void	error_see(void)
{
	ft_printf("%s\n", strerror(errno));
	exit(-1);
}

void	error_file(char *str)
{
	ft_printf("ls: %s: No such file or directory\n", str);
	exit(1);
}

void	error_test(int i)
{
	ft_printf("Ton ls crash: %d\n", i);
	exit(1);
}
