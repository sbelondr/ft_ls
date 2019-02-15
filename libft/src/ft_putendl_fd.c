/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:57:14 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/05 21:25:00 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
#include <unistd.h>

void	ft_putendl_fd(char const *s, int fd)
{
	char	c;

	c = '\n';
	write(fd, s, ft_strlen(s));
	write(fd, &c, 1);
}
