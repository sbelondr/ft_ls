/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:20:22 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/12 13:49:49 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static int	ft_endline(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (i);
	return (i);
}

static int	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (-1);
}

static int	ft_read_line(const int fd, char **str)
{
	char		buff[BUFF_S + 1];
	char		*tmp;
	int			verif;

	ft_bzero(buff, BUFF_S);
	while ((verif = read(fd, buff, BUFF_S)) > 0)
	{
		buff[verif] = '\0';
		tmp = ft_strjoin(*str, buff);
		ft_free(&(*str));
		if (tmp)
		{
			if (!(*str = ft_strdup(tmp)))
				return (-1);
			ft_free(&tmp);
			if (ft_strchr(*str, '\n') != 0)
				break ;
		}
	}
	if (verif == -1)
		ft_free(&(*str));
	return (verif);
}

static int	ft_verif(int fd, char **line, char **str)
{
	static	int	verif;

	if (fd < 0 || line == NULL)
		return (-1);
	if (!(*str) || ((*str) && ft_strcmp(*str, "") == 0) || fd != verif)
	{
		verif = fd;
		if (!(*str = ft_strnew(BUFF_S)))
			return (-1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*str;
	char		*tmp;
	int			len;
	int			verif;

	if (ft_verif(fd, &(*line), &str) == -1)
		return (ft_free(&str));
	verif = ft_read_line(fd, &str);
	if (verif == -1)
		return (ft_free(&str));
	len = ft_endline(str);
	if (str[0])
	{
		*line = (len == 0) ? ft_strdup("") : ft_strsub(str, 0, len);
		tmp = (len + 1 < (int)ft_strlen(str)) ? ft_strdup(str + len + 1) :
			ft_strdup("");
		ft_strdel(&str);
		if (tmp)
			str = ft_strdup(tmp);
		ft_free(&tmp);
		return (1);
	}
	else
		*line = ft_strdup("");
	return (0);
}
