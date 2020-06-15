/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 13:21:17 by greed         #+#    #+#                 */
/*   Updated: 2019/11/08 19:24:10 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int		ft_fatoi(const char *str, unsigned long int res, int sign)
{
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
		if (res > 9223372036854775807UL && sign == 1)
			return (-1);
		else if (res > 9223372036854775808UL && sign == -1)
			return (0);
	}
	return (res);
}

int					ft_atoi(const char *str)
{
	int					sign;
	unsigned long int	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str == '+')
		str++;
	res = ft_fatoi(str, res, sign);
	return (sign * (int)res);
}
