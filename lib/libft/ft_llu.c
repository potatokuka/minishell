/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_llu.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 12:53:49 by greed         #+#    #+#                 */
/*   Updated: 2020/05/25 13:31:47 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void		ft_llu(t_conv *conv, va_list a_list, int *lv)
{
	if (conv->size == 1 || conv->size == 2)
		ft_llu_num(conv, a_list, lv);
}

void		ft_llu_num(t_conv *conv, va_list a_list, int *lv)
{
	unsigned long long num;

	num = va_arg(a_list, unsigned long long);
	ft_conv_llu_int(conv, num);
	if (conv->hassign && (conv->padzero || conv->left))
		ft_putchar_c_fd(conv->sign, 1, lv);
	if (conv->left)
	{
		ft_pad_width(conv->precision, conv->numlen, '0', lv);
		if (conv->precision)
			ft_lluint_c_fd(num, lv);
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
			ft_lluint_c_fd(num, lv);
	}
}

void		ft_lluint_c_fd(unsigned long long num, int *lv)
{
	unsigned long long	res;
	unsigned long long	power;

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

int			ft_llu_nbr_size(unsigned long long num)
{
	unsigned long long	tmp;
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

void		ft_conv_llu_int(t_conv *conv, unsigned long long num)
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
