/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 16:43:13 by greed         #+#    #+#                 */
/*   Updated: 2019/11/08 12:16:35 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_numlen(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char		*ft_memorysize(int len)
{
	char	*res;

	res = (char*)malloc(len);
	if (res == NULL)
		return (NULL);
	res[len - 1] = '\0';
	return (res);
}

static char		*ft_exceptions(int n)
{
	char	*res;

	res = (char*)malloc((n == 0) ? 2 : 13);
	if (!(res))
		return (NULL);
	if (n == 0)
		ft_strlcpy(res, "0", 2);
	else
		ft_strlcpy(res, "-2147483648", 12);
	return (res);
}

static char		ft_solver(int sign, int nbr_len, int n, char *res)
{
	int i;

	i = -1;
	while (i + 1 < nbr_len - sign)
	{
		i++;
		res[nbr_len - 1 - i] = (char)(n % 10 + '0');
		n /= 10;
	}
	return (*res);
}

char			*ft_itoa(int n)
{
	int		nbr_len;
	int		sign;
	char	*res;

	sign = n < 0;
	nbr_len = ft_numlen(n);
	if (n == -2147483648 || n == 0)
		return (ft_exceptions(n));
	res = ft_memorysize(nbr_len + 1);
	if (res == NULL)
		return (NULL);
	if (sign)
	{
		*res = '-';
		n *= -1;
	}
	ft_solver(sign, nbr_len, n, res);
	return (res);
}
