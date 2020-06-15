/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 10:15:46 by greed         #+#    #+#                 */
/*   Updated: 2019/12/07 13:07:43 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_flag_vars_set(t_conv *conv)
{
	conv->left = 0;
	conv->hash = 0;
	conv->padzero = 0;
	conv->width = 0;
	conv->precision = -2;
	conv->sign = 0;
	conv->len = 0;
	conv->hassign = 0;
	conv->numlen = 0;
	conv->size = 0;
	conv->count = 0;
}

void		ft_converter_link(t_conv *conv, va_list a_list, int *lv)
{
	char	*types;
	t_cfunc	funcs[10];
	int		i;

	types = "cspdiuxXn%";
	funcs[0] = &ft_print_char;
	funcs[1] = &ft_print_string;
	funcs[2] = &ft_print_pointer;
	funcs[3] = &ft_int_link;
	funcs[4] = &ft_int_link;
	funcs[5] = &ft_uint_link;
	funcs[6] = &ft_x_link;
	funcs[7] = &ft_up_x_link;
	// funcs[8] = &ft_print_count;
	funcs[9] = &ft_print_pct;
	i = 0;
	while (types[i])
	{
		if (types[i] == conv->type)
			funcs[i](conv, a_list, lv);
		i++;
	}
}

int			ft_printf(const char *input, ...)
{
	va_list a_list;
	t_conv	conv;
	int		lv;

	va_start(a_list, input);
	lv = 0;
	while (*input)
	{
		if (*input != '%')
			ft_putchar_c_fd(*input, 1, &lv);
		else
		{
			ft_flag_vars_set(&conv);
			ft_find_type(&input, &conv);
			if (conv.width == -1)
				conv.width = va_arg(a_list, int);
			if (conv.precision == -1)
				conv.precision = va_arg(a_list, int);
			ft_converter_link(&conv, a_list, &lv);
		}
		input++;
	}
	va_end(a_list);
	return (lv);
}
