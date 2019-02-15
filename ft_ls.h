/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:45:34 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/15 09:58:11 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FT_LS_H
#	define FT_LS_H

#include "libft/headers/libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>

#include <stdio.h>

struct dirent*		readdir(DIR* repertoire);

typedef struct		s_ls
{
	char			flags[10];
	char			**options;
	DIR				*rep;
	int				total;
	struct dirent*	read_file;
}					t_ls;

typedef struct		s_read
{
	t_ls			*ls;
	char			*name;
	struct stat		file_stat;
	struct passwd	*pwuser;
	struct group	*grpname;
	char			path[1024];
	char			perm[11];
	char			time_last_edit[BUFF_S];
	struct s_read	*next;
}					t_read;

typedef struct		s_save
{
	t_read			*p_start;
	t_read			*list;
}					t_save;

/*
** ft_ls.c
*/

int					ft_ls(int ac, char **av);

/*
** open.c
*/

int					ft_open_ls(t_ls **ls, int index);
void				sv_next(t_save *sv);
void				sv_first(t_save *sv);
size_t				sv_size(t_save *sv);
void				sv_remove_next(t_save *sv);
void				sv_remove_first(t_save *sv);
void				sv_delete(t_save **sv);


/*
** sort.c
*/

void				ft_sort_ls(t_save **sv, t_ls **ls, int index);
void				ft_ls_recursive(t_save *sv);

/*
** error.c
*/

void				error_option(char c);
void				error_file(char *str);
void				error_test(int i);

/*
** display.c
*/

void				display_read(t_ls *ls, t_save *sv);

#	endif
