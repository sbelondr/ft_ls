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
}

void	error_permissions(t_read *r)
{
	char	*str;
	char	*tmp;
	char	*dst;

	str = ft_strdup("ls: ");
	tmp = ft_strdup(": Permission denied");
	dst = ft_strjoin(str, r->name);
	ft_strdel(&str);
	str = ft_strjoin(dst, tmp);
	ft_strdel(&dst);
	dst = ft_strjoin(str, "\n");
	write(2, dst, ft_strlen(dst));
	ft_strdel(&str);
	ft_strdel(&dst);
	ft_strdel(&tmp);
}

void	error_rep(char *str)
{
	char	*tmp;
	char	*dst;

	tmp = ft_strjoin("ls: ", str);
	dst = ft_strjoin(tmp, ": ");
	ft_strdel(&tmp);
	tmp = ft_strjoin(dst, strerror(errno));
	ft_strdel(&dst);
	dst = ft_strjoin(tmp, "\n");
	write(2, dst, ft_strlen(dst));
	ft_strdel(&dst);
	ft_strdel(&tmp);
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
