/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 10:44:15 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/13 12:37:04 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

void	ft_stock(t_printf **lst, char dst[BUFF_S], int (*stock)[3])
{
	(*stock)[0] = ft_strchr_exist((*lst)->options, '+');
	(*stock)[1] = ft_strchr_exist((*lst)->options, '-');
	(*stock)[2] = (*lst)->large_min - ((int)ft_strlen(dst) + (*stock)[0]);
	if (((*lst)->flag == 'd' || (*lst)->flag == 'i') && (*stock)[0])
		(*stock)[2] += ft_strchr_exist(dst, '-');
}

void	ft_cpy_str(char (*dst)[BUFF_S], char str[BUFF_S])
{
	int	i;

	i = -1;
	while (str[++i])
		(*dst)[i] = str[i];
	while (i < BUFF_S)
		(*dst)[i++] = '\0';
}

char	*ft_large_str(int l, char c)
{
	char	str[BUFF_S];
	char	*tmp;
	int		i;

	i = -1;
	ft_bzero(&str, BUFF_S);
	ft_large(&str, l, c);
	if (!(tmp = (char*)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[++i])
		tmp[i] = str[i];
	tmp[i] = '\0';
	return (tmp);
}

void	ft_large(char (*buff)[BUFF_S], int l, char c)
{
	int		i;

	i = -1;
	while (++i < l)
		(*buff)[i] = c;
	while (i < BUFF_S)
		(*buff)[i++] = '\0';
}

void	ft_join(char (*dst)[BUFF_S], char *str, int ordre)
{
	int		i;
	int		j;
	char	tmp[BUFF_S];

	i = -1;
	j = -1;
	ft_bzero(&tmp, BUFF_S);
	if (ordre == 0)
	{
		while ((*dst)[++i])
			tmp[i] = (*dst)[i];
		while (str[++j])
			tmp[i++] = str[j];
	}
	else
	{
		while (str[++i])
			tmp[i] = str[i];
		while ((*dst)[++j])
			tmp[i++] = (*dst)[j];
	}
	ft_cpy_str(&(*dst), tmp);
}
