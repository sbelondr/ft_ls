/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:39:03 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/13 16:01:59 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	ft_blank_list(t_printf **lst)
{
	if (!((*lst) = (t_printf*)malloc(sizeof(t_printf) * 1)))
		return ;
	ft_bzero(&(*lst)->options, 50);
	ft_bzero(&(*lst)->conversion, 3);
	(*lst)->large_min = 0;
	(*lst)->precision = -2;
	(*lst)->flag = '0';
	(*lst)->value = 0;
	(*lst)->len = 0;
	(*lst)->index = 0;
}

void	ft_reset_value(t_printf **lst)
{
	ft_bzero(&(*lst)->options, 50);
	ft_bzero(&(*lst)->conversion, 3);
	(*lst)->large_min = 0;
	(*lst)->precision = -2;
	(*lst)->flag = '0';
	(*lst)->value = 0;
}

char	*insert_format(const char *e)
{
	int		i;
	char	*format;

	i = -1;
	format = (char*)malloc(sizeof(char) * ft_strlen(e) + 1);
	while (e[++i])
		format[i] = e[i];
	format[i] = '\0';
	return (format);
}

int		ft_prepare(const char *format, t_printf **lst)
{
	if (!format)
		return (0);
	ft_blank_list(&(*lst));
	(*lst)->format = insert_format(format);
	return (1);
}

int		ft_printf(const char *format, ...)
{
	int			len;
	t_printf	*lst;

	if (ft_prepare(format, &lst) == 0)
		return (0);
	va_start((lst)->ap, format);
	while (lst->format[lst->index])
	{
		if (lst->format[lst->index] == '%')
		{
			ft_reset_value(&lst);
			ft_manage(&lst);
		}
		else
		{
			ft_putchar(lst->format[lst->index]);
			lst->len++;
		}
		lst->index++;
	}
	va_end(lst->ap);
	len = lst->len;
	ft_strdel(&(lst->format));
	free(lst);
	return (len);
}
