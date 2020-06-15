/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_uint.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/15 12:14:25 by greed         #+#    #+#                 */
/*   Updated: 2019/12/07 13:08:25 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void			ft_print_uint(t_conv *conv, va_list a_list, int *lv)
{
	unsigned int		num;

	num = va_arg(a_list, unsigned int);
	ft_conv_uint(conv, num);
	if (conv->hassign && (conv->padzero || conv->left))
		ft_putchar_c_fd(conv->sign, 1, lv);
	if (conv->left)
	{
		ft_pad_width(conv->precision, conv->numlen, '0', lv);
		if (conv->precision)
			ft_u_intres_c_fd(num, lv);
	}
	if (!conv->left && conv->padzero)
		ft_pad_width(conv->width, conv->precision + conv->hassign, '0', lv);
	else
		ft_pad_width(conv->width, conv->precision + conv->hassign, ' ', lv);
	if (!conv->left)
	{
		if (conv->hassign && !conv->padzero)
			ft_putchar_c_fd(conv->sign, 1, lv);
		ft_pad_width(conv->precision, conv->numlen, '0', lv);
		if (conv->precision)
			ft_u_intres_c_fd(num, lv);
	}
}

unsigned int	ft_uint_size(unsigned int num)
{
	unsigned int		tmp;
	int					size;

	tmp = num;
	size = 0;
	if (num == 0)
		size++;
	while (tmp)
	{
		tmp = tmp / 10;
		size++;
	}
	return (size);
}

void			ft_conv_uint(t_conv *conv, unsigned int num)
{
	if (num < 0)
	{
		conv->hassign = 1;
		conv->sign = '-';
	}
	conv->numlen = ft_uint_size(num);
	if (conv->precision != -2)
		conv->padzero = 0;
	if (conv->precision == -2 ||
		(conv->precision < conv->numlen && conv->precision != 0))
		conv->precision = conv->numlen;
}

void			ft_u_intres_c_fd(unsigned int num, int *lv)
{
	unsigned int		res;
	unsigned int		power;

	res = num;
	power = 1;
	while (res / 10)
	{
		res /= 10;
		power *= 10;
	}
	while (power)
	{
		if (num < 0)
			ft_putchar_c_fd(('0' - num / power), 1, lv);
		if (!(num < 0))
			ft_putchar_c_fd(('0' + num / power), 1, lv);
		num %= power;
		power /= 10;
	}
}
