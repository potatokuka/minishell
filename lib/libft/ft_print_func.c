/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_func.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 16:18:54 by greed         #+#    #+#                 */
/*   Updated: 2020/06/20 13:46:26 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_print_char(t_conv *conv, va_list a_list, int *lv)
{
	int			c;

	c = va_arg(a_list, int);
	if (conv->precision == -2)
		conv->precision = 1;
	if (conv->left)
	{
		*lv += 1;
		ft_putchar_fd(c, conv->fd);
	}
	ft_pad_width(conv->width, conv->precision, ' ', lv);
	if (!(conv->left))
	{
		*lv += 1;
		ft_putchar_fd(c, conv->fd);
	}
}

void		ft_print_string(t_conv *conv, va_list a_list, int *lv)
{
	char		*str;

	str = va_arg(a_list, char*);
	if (!(str))
		str = "(null)";
	conv->len = ft_strlen(str);
	if (conv->precision == -2 || conv->precision > conv->len)
		conv->precision = conv->len;
	if (conv->left)
		ft_putstr_c_fd(str, conv->fd, conv->precision, lv);
	if (!conv->left && conv->padzero)
		ft_pad_width(conv->width, conv->precision, '0', lv);
	else
		ft_pad_width(conv->width, conv->precision, ' ', lv);
	if (!(conv->left))
		ft_putstr_c_fd(str, conv->fd, conv->precision, lv);
}

void		ft_putchar_c_fd(char c, int fd, int *lv)
{
	ft_putchar_fd(c, fd);
	*lv += 1;
}

void		ft_print_pct(t_conv *conv, va_list a_list, int *lv)
{
	va_list b_list;

	va_copy(b_list, a_list);
	va_end(b_list);
	if (conv->precision == -2)
		conv->precision = 1;
	if (conv->left)
	{
		*lv += 1;
		ft_putchar_fd('%', conv->fd);
	}
	if (!conv->left && conv->padzero)
		ft_pad_width(conv->width, conv->precision, '0', lv);
	else
		ft_pad_width(conv->width, conv->precision, ' ', lv);
	if (!(conv->left))
	{
		*lv += 1;
		ft_putchar_fd('%', conv->fd);
	}
}

void		ft_print_count(t_conv *conv, va_list a_list, int *lv)
{
	int		*count;

	*conv = *conv;
	count = va_arg(a_list, int*);
	*count = *lv;
}
