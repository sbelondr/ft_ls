/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 19:42:20 by sbelondr          #+#    #+#             */
/*   Updated: 2019/02/21 17:40:12 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef FT_PRINTF_H
#	define FT_PRINTF_H

#include "libft/headers/libft.h"
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

void				ft_large_min(char (*dst)[BUFF_S], t_printf *lst,
		int stock[3]);

/*
** apply_arg_float.c
*/

void				ft_apply_arg_float(char (*str)[BUFF_S], t_printf **lst,
		int neg);

/*
** display.c
*/

void				ft_display(char dst[BUFF_S], t_printf **lst);

/*
** tools.c
*/

void				ft_cpy_str(char (*dst)[BUFF_S], char *str);
void				ft_large(char (*buff)[BUFF_S], int l, char c);
void				ft_join(char (*dst)[BUFF_S], char *str, int ordre);
void				ft_stock(t_printf **lst, char dst[BUFF_S], int (*stock)[3]);

/*
** tools_float_bis.c
*/

char				*ft_precision_float(char (*dst)[BUFF_S], t_printf **lst);
int					check_p(char dst[BUFF_S], int precision, int i);
char				*ft_round_precision(char (*dst)[BUFF_S], int precision);
int					len_float(t_printf **lst, int stock[3], int neg);

/*
** ft_itoa_other.c
*/
int					ft_len_unsigned(unsigned long long n);
int					ft_len_long(long long n);
char				*ft_itoa_long(long long n);
char				*ft_itoa_s(short n);

/*
** ft_itoa_other_u_s.c
*/
char				*ft_itoa_sc(signed char n);
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
** tools_bis.c
*/

char				ft_alpha(unsigned int nb);
void				ft_startjoin_50(char (*str)[50], char c);
void				result_null(t_printf **lst, char (*str)[BUFF_S]);

/*
** tools_float.c
*/

void				ft_inf_nan(char (*str)[BUFF_S], t_printf **lst,
		int stock[3]);
char				*apply_round_i(char dst[BUFF_S], int *i, int precision);
char				*apply_round_ni(char dst[BUFF_S]);
void				apply_round_final(int stock, char **tmp, int i);
char				*ft_apply_round(char (*dst)[BUFF_S], int stock,
		int precision);

/*
** manage_float.c
*/

void				ft_gest_float(char (*tab)[BUFF_S], int d);

/*
** multiplication_float.c
*/

void				tablo_calc(char (*tab)[BUFF_S], int base);
void				mult_mantissa(char (*tab)[BUFF_S], int d);

/*
** add_float.c
*/

void				add_mantissa(char (*tab)[BUFF_S], char tab_b[BUFF_S]);
void				ft_add_zero(char (*tab)[BUFF_S], int len);
void				add_float(char (*tab)[BUFF_S], char (*tab_b)[BUFF_S]);

/*
** apply_arg_s.c
*/

void				apply_arg_s(char *str, t_printf **lst);
void				apply_arg_c(char c, t_printf **lst);

/*
** apply_arg_n.c
*/

void				apply_arg_n(char *str, t_printf **lst);
char				*precision_n(char *str, t_printf **lst, int neg);
void				options_n(t_printf **lst, int stock[3], int neg, int rd);

/*
** apply_arg_convert.c
*/

void				apply_arg_convert(char *str, t_printf **lst);
void				apply_hash_p(t_printf **lst);

#	endif
