/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:45:34 by sbelondr          #+#    #+#             */
/*   Updated: 2019/03/05 15:24:55 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FT_LS_H
#	define FT_LS_H

#include "../libft/headers/libft.h"
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <uuid/uuid.h>
#include <time.h>
#include <sys/xattr.h>

struct dirent		*readdir(DIR *repertoire);

typedef struct		s_ls
{
	char			flags[10];
	DIR				*rep;
	long long		total;
	char			**options;
	struct dirent	*read_file;
	int				column[8];
}					t_ls;

typedef struct		s_read
{
	t_ls			*ls;
	char			*name;
	struct stat		file_stat;
	struct passwd	*pwuser;
	struct group	*grpname;
	char			path[BUFF_S];
	char			perm[11];
	char			mois[BUFF_S];
	char			jour[BUFF_S];
	char			year_or_hours[BUFF_S];
	char			symbolic_link[BUFF_S];
	struct s_read	*next;
}					t_read;

typedef struct		s_save
{
	t_read			*p_start;
	t_read			*list;
	t_read			*list_last;
}					t_save;

/*
** ft_ls.c
*/

int					ft_ls(int ac, char **av);

/*
** parser.c
*/

int					parser(int ac, char **flags, t_ls **ls);

/*
** error.c
*/

void				error_option(char c);
void				error_see(void);
void				error_rep(char *str);
void				error_permissions(t_read *r);

/*
** open.c
*/

int					open_ls(t_ls **ls, int index, int see_folder, int first);

/*
** insert.c
*/

int					insert_read(t_ls **ls, int index, t_save **sv);
int					insert_read_sl(t_ls **ls, int index);
int					insert_read_file(t_ls **ls, int index);

/*
** list.c
*/

t_save				*init_sv(void);
void				insert_sv(t_save **sv, t_read *r);
void				next_sv(t_save *sv);
void				first_sv(t_save *sv);
size_t				size_sv(t_save *sv);

/*
** list_remove.c
*/

void				delete_sv(t_save **sv, int cnt);

/*
** display.c
*/

void				display_read(t_ls *ls, t_save *sv, int break_line);

/*
** sort.c
*/

void				ft_sort_ls(t_save **sv, t_ls **ls);

#	endif
