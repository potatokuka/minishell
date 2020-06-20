/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 13:35:04 by greed         #+#    #+#                 */
/*   Updated: 2020/06/20 17:59:38 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_fd(int fd, const char *input, ...)
{
	va_list a_list;
	t_conv	conv;
	int		lv;

	va_start(a_list, input);
	lv = 0;
	conv.fd = fd;
	while (*input)
	{
		if (*input != '%')
			ft_putchar_c_fd(*input, fd, &lv);
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
