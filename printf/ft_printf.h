/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:09:11 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 18:40:33 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <ctype.h>
# include <stdarg.h>

typedef struct	s_struct
{
	char		*copy;
	char		*x;
	va_list		va_lues;
	int			len;
	int			flags;
	int			width;
	int			precision;
	int			start_precision;
	int			take_arg;
	int			take_second_arg;
	int			n;
	int			i;
	int			total_return;
}				t_struct;

int				ft_printf(const char *arr, ...);
void			ft_all_values_to_start(t_struct *base);
void			ft_restart_values(t_struct *base);
int				ft_super_function(t_struct *base);
void			ft_x(t_struct *base);
void			ft_big_x(t_struct *base);
void			ft_c(t_struct *base);
void			ft_d(t_struct *base);
void			ft_i(t_struct *base);
void			ft_p(t_struct *base);
void			ft_s(t_struct *base);
void			ft_u(t_struct *base);
void			ft_rest(t_struct *base);
char			*ft_convert_to_hex(unsigned long int x);
void			ft_precision(t_struct *base);
void			ft_width(t_struct *base);
void			ft_put(t_struct *base);
char			*ft_strupcase(char *str);
void			ft_my_args(t_struct *base);
int				ft_write_and_sum(t_struct *base);
void			ft_new_me(t_struct *base, char c);
int				ft_toupper(int c);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strndup(const char *s, int n);
void			ft_putstr_fd(char *s);
void			ft_putnbr_fd(int n);
void			ft_putchar_fd(char c);
int				len(long nb);
char			*ft_itoa(int nb);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_atoi(const char *j);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *str, int c);
void			*ft_calloc(size_t count, size_t size);
char			*ft_itoa2(unsigned int nb);
void			ft_put2(t_struct *base);
char			*ft_strlowcase(char *str);
void			ft_free(t_struct *base, int x);
void			ft_width_p(t_struct *base);
#endif
