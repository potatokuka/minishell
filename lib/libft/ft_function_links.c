/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_function_links.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/19 14:59:03 by greed         #+#    #+#                 */
/*   Updated: 2019/12/07 13:08:25 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_uint_link(t_conv *conv, va_list a_list, int *lv)
{
	if (conv->size == 1 || conv->size == 2)
		return (ft_llu_num(conv, a_list, lv));
	else
		return (ft_print_uint(conv, a_list, lv));
}

void		ft_int_link(t_conv *conv, va_list a_list, int *lv)
{
	if (conv->size == 1 || conv->size == 2)
		ft_ll_num(conv, a_list, lv);
	else
		return (ft_print_int(conv, a_list, lv));
}

void		ft_x_link(t_conv *conv, va_list a_list, int *lv)
{
	if (conv->size == 1 || conv->size == 2)
		return (ft_print_ll_x(conv, a_list, lv));
	else
		return (ft_print_x(conv, a_list, lv));
}

void		ft_up_x_link(t_conv *conv, va_list a_list, int *lv)
{
	if (conv->size == 1 || conv->size == 2)
		return (ft_print_ll_up_x(conv, a_list, lv));
	else
		return (ft_print_up_x(conv, a_list, lv));
}
