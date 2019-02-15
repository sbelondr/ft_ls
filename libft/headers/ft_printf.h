/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 19:42:20 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/12 16:02:41 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FT_PRINTF_H
#	define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>
#include <strings.h>

typedef struct		s_printf
{
	va_list			ap;
	char			*format;
	char			options[50];
	char			conversion[3];
	size_t			large_min;
	int				precision;
	char			flag;
	double			value;
	int				len;
	int				index;
}					t_printf;

typedef uint64_t	t_u64;

/*
** binary.c
*/

void				ft_see_binary_u64(t_u64 nb);
char				ft_binary_to_char(t_u64 nb);

/*
** ft_printf.c
*/
int					ft_printf(const char *format, ...);

/*
** parser.c
*/
void				ft_manage(t_printf **lst);

/*
** gest_flag.c
*/

void				ft_gest_flag(t_printf **lst);

/*
** arg_s.c
*/

void				ft_arg_s(t_printf **lst);
void				ft_arg_c(t_printf **lst);
void				ft_arg_percent(t_printf **lst);

/*
** arg_n.c
*/

void				ft_arg_d(t_printf **lst);
void				ft_arg_u(t_printf **lst);

/*
** arg_convert.c
*/

void				ft_arg_x(t_printf **lst);
void				ft_arg_o(t_printf **lst);
void				ft_arg_pointer(t_printf **lst);

/*
** arg_float.c
*/

void				ft_arg_float(t_printf **lst);

/*
** apply_arg.c
*/

void				ft_apply_arg(char *str, t_printf **lst);
void				ft_precision(char (*dst)[BUFF_S], t_printf *lst);
void				ft_large_min(char (*dst)[BUFF_S], t_printf *lst,
		int stock[3]);

/*
** apply_arg_float.c
*/

void				ft_apply_arg_float(char (*str)[BUFF_S], t_printf **lst);

/*
** display.c
*/

void				ft_display(char dst[BUFF_S], t_printf **lst);

/*
** tools.c
*/

void				ft_cpy_str(char (*dst)[BUFF_S], char *str);
char				*ft_large_str(int l, char c);
void				ft_large(char (*buff)[BUFF_S], int l, char c);
void				ft_join(char (*dst)[BUFF_S], char *str, int ordre);
void				ft_stock(t_printf **lst, char dst[BUFF_S], int (*stock)[3]);

/*
** ft_itoa_other.c
*/
int					ft_len_unsigned(unsigned long long n);
int					ft_len_long(long long n);
char				*ft_itoa_simple_long(long n);
char				*ft_itoa_long(long long n);
char				*ft_itoa_s(short n);

/*
** ft_itoa_other_u_s.c
*/
char				*ft_itoa_sc(signed char n);
char				*ft_itoa_ui(unsigned int n);
char				*ft_itoa_ul(unsigned long long n);
char				*ft_itoa_us(unsigned short n);

/*
** ft_convert_base.c
*/

void				ft_convert_base(unsigned int nb, int base,
		char (*str)[BUFF_S]);
void				ft_convert_base_uc(unsigned char nb, int base,
		char (*str)[BUFF_S]);
void				ft_convert_base_us(unsigned short nb, int base,
		char (*str)[BUFF_S]);
void				ft_convert_base_ll(unsigned long long nb, int base,
		char (*str)[BUFF_S]);
void				ft_startjoin(char (*str)[BUFF_S], char c);

/*
** tools_apply_arg.c
*/

void				verif_p(char (*dst)[BUFF_S], t_printf **lst);
int					ft_exception(t_printf *lst);
void				check_space(t_printf *lst, char (*dst)[BUFF_S]);
void				manage_plus_decimal(char (*dst)[BUFF_S], t_printf *lst,
		int stock[3]);

/*
** tools_bis.c
*/

char				ft_alpha(unsigned int nb);
void				ft_correct_reverse(char (*dst)[BUFF_S], char a, char b);
void				ft_startjoin_50(char (*str)[50], char c);
void				result_null(t_printf **lst, char (*str)[BUFF_S]);
void				ft_correct_x(char (*dst)[BUFF_S], char a, char b);

/*
** tools_float.c
*/

void				ft_inf_nan(char (*str)[BUFF_S], t_printf **lst,
		int stock[3]);
void				ft_large_min_float(int len, char c, char (*dst)[BUFF_S]);

/*
** manage_float.c
*/

void				ft_gest_float(char (*tab)[BUFF_S], int d);

/*
** tools_n.c
*/

void				ft_precision_u_correct(t_printf **lst, char *str);
int					ft_verif_space_n(t_printf **lst, char *str);
void				ft_affiche_n_null(t_printf **lst);
void				ft_correct(char (*dst)[BUFF_S], char a, char b,
		t_printf **lst);

/*
** multiplication_float.c
*/

void				tablo_calc(char (*tab)[BUFF_S], int base);
void				mult_mantissa(char (*tab)[BUFF_S], int d);

/*
** round_float.c
*/

void				ft_round_final(char (*tab)[BUFF_S]);
void				ft_round_str(char (*tab)[BUFF_S], int round);

/*
** add_float.c
*/

void				add_mantissa(char (*tab)[BUFF_S], char tab_b[BUFF_S]);
void				ft_add_zero(char (*tab)[BUFF_S], int len);
void				add_float(char (*tab)[BUFF_S], char (*tab_b)[BUFF_S]);

#	endif
