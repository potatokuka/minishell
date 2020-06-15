/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_x.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/15 13:39:27 by greed         #+#    #+#                 */
/*   Updated: 2019/12/07 13:08:25 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void		ft_print_x(t_conv *conv, va_list a_list, int *lv)
{
	unsigned int		num;

	num = va_arg(a_list, unsigned int);
	ft_conv_x(conv, &num);
	if (conv->hash && num != 0 && (conv->left || conv->padzero))
		ft_putstr_c_fd("0x", 1, 2, lv);
	if (conv->left)
	{
		ft_pad_width(conv->precision, conv->numlen, '0', lv);
		if (conv->precision)
			ft_x_res_c_fd(num, lv);
	}
	if (!conv->left && conv->padzero)
		ft_pad_width(conv->width, conv->precision + (conv->hash * 2), '0', lv);
	else
		ft_pad_width(conv->width, conv->precision + (conv->hash * 2), ' ', lv);
	if (!conv->left)
	{
		if (conv->hash && num != 0 && !conv->padzero)
			ft_putstr_c_fd("0x", 1, 2, lv);
		ft_pad_width(conv->precision, conv->numlen, '0', lv);
		if (conv->precision)
			ft_x_res_c_fd(num, lv);
	}
}

void		ft_conv_x(t_conv *conv, unsigned int *num)
{
	conv->numlen = ft_x_size(*num);
	if (conv->precision != -2)
		conv->padzero = 0;
	if (*num == 0)
		conv->hash = 0;
	if (conv->precision == -2 || (conv->precision < conv->numlen && *num != 0))
		conv->precision = conv->numlen;
}

void		ft_x_res_c_fd(unsigned int num, int *lv)
{
	unsigned int		res;
	unsigned int		power;
	char				*hex;

	hex = "0123456789abcdef";
	res = num;
	power = 1;
	while (res / 16)
	{
		res /= 16;
		power *= 16;
	}
	res = num;
	while (power)
	{
		ft_putchar_c_fd(hex[num / power], 1, lv);
		num %= power;
		power /= 16;
	}
}

void		ft_upx_res_c_fd(unsigned int num, int *lv)
{
	unsigned int		res;
	unsigned int		power;
	char				*hex;

	hex = "0123456789ABCDEF";
	res = num;
	power = 1;
	while (res / 16)
	{
		res /= 16;
		power *= 16;
	}
	res = num;
	while (power)
	{
		ft_putchar_c_fd(hex[num / power], 1, lv);
		num = num % power;
		power /= 16;
	}
}

void		ft_print_up_x(t_conv *conv, va_list a_list, int *lv)
{
	unsigned int		num;

	num = va_arg(a_list, unsigned int);
	ft_conv_x(conv, &num);
	if (conv->hash && num != 0 && (conv->left || conv->padzero))
		ft_putstr_c_fd("0X", 1, 2, lv);
	if (conv->left)
	{
		ft_pad_width(conv->precision, conv->numlen, '0', lv);
		if (conv->precision)
			ft_upx_res_c_fd(num, lv);
	}
	if (!conv->left && conv->padzero)
		ft_pad_width(conv->width, conv->precision + (conv->hash * 2), '0', lv);
	else
		ft_pad_width(conv->width, conv->precision + (conv->hash * 2), ' ', lv);
	if (!conv->left)
	{
		if (conv->hash && num != 0 && !conv->padzero)
			ft_putstr_c_fd("0X", 1, 2, lv);
		ft_pad_width(conv->precision, conv->numlen, '0', lv);
		if (conv->precision)
			ft_upx_res_c_fd(num, lv);
	}
}
