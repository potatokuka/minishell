/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pointer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 15:37:14 by greed         #+#    #+#                 */
/*   Updated: 2019/12/07 13:07:54 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_print_pointer(t_conv *conv, va_list a_list, int *lv)
{
	unsigned long ptr;

	ptr = (unsigned long)va_arg(a_list, void*);
	conv->numlen = (ft_ptr_size(ptr) + 2);
	if (conv->precision == -2 ||
		(conv->precision < conv->numlen && conv->precision != 0))
		conv->precision = conv->numlen;
	if (conv->left)
	{
		ft_putstr_c_fd("0x", 1, 2, lv);
		ft_pad_width(conv->precision,
			conv->numlen - ((conv->precision > conv->numlen) ? 2 : 0), '0', lv);
		if (conv->precision)
			ft_ptr_res_fd(ptr, lv);
	}
	(!conv->left && conv->padzero) ? ft_pad_width(conv->width, conv->precision,
		'0', lv) : ft_pad_width(conv->width, conv->precision, ' ', lv);
	if (!(conv->left))
	{
		ft_putstr_c_fd("0x", 1, 2, lv);
		ft_pad_width(conv->precision,
			conv->numlen - ((conv->precision > conv->numlen) ? 2 : 0), '0', lv);
		if (conv->precision)
			ft_ptr_res_fd(ptr, lv);
	}
}

unsigned long		ft_ptr_size(unsigned long ptr)
{
	unsigned long		tmp;
	unsigned long		size;

	size = 0;
	tmp = ptr;
	if (ptr == 0)
		size++;
	while (tmp)
	{
		tmp = tmp / 16;
		size++;
	}
	return (size);
}

void				ft_ptr_res_fd(unsigned long ptr, int *lv)
{
	unsigned long		res;
	unsigned long		power;
	char				*hex;

	hex = "0123456789abcdef";
	res = ptr;
	power = 1;
	while (res / 16)
	{
		res /= 16;
		power *= 16;
	}
	res = ptr;
	while (power)
	{
		ft_putchar_c_fd(hex[ptr / power], 1, lv);
		ptr %= power;
		power /= 16;
	}
}
