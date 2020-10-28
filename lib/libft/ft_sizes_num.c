/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sizes_num.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/16 16:20:16 by greed         #+#    #+#                 */
/*   Updated: 2019/12/07 13:08:25 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_ll_num(t_conv *conv, va_list a_list, int *lv)
{
	long long int num;

	num = va_arg(a_list, long long int);
	ft_conv_ll_int(conv, num);
	if (conv->hassign && (conv->padzero || conv->left))
		ft_putchar_c_fd(conv->sign, 1, lv);
	if (conv->left)
	{
		ft_pad_width(conv->precision, conv->numlen, '0', lv);
		if (conv->precision)
			ft_llint_c_fd(num, lv);
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
			ft_llint_c_fd(num, lv);
	}
}

void				ft_llint_c_fd(long long int num, int *lv)
{
	long long int		res;
	long long int		power;

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

long long int		ft_ll_nbr_size(long long int num)
{
	long long int		tmp;
	long long int		size;

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

void				ft_conv_ll_int(t_conv *conv, long long int num)
{
	if (num < 0)
	{
		conv->hassign = 1;
		conv->sign = '-';
	}
	conv->numlen = ft_ll_nbr_size(num);
	if (conv->precision != -2)
		conv->padzero = 0;
	if (conv->precision == -2 ||
		(conv->precision < conv->numlen && conv->precision != 0))
		conv->precision = conv->numlen;
}
