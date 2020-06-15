/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 17:10:12 by greed         #+#    #+#                 */
/*   Updated: 2019/11/08 14:36:09 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_mover(unsigned char *dest, const unsigned char *srcs, size_t len)
{
	size_t				i;

	if (dest < srcs)
	{
		i = 0;
		while (i < len)
		{
			dest[i] = srcs[i];
			i++;
		}
	}
	else if (dest > srcs)
	{
		i = len;
		while (i > 0)
		{
			dest[i - 1] = srcs[i - 1];
			i--;
		}
	}
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	const unsigned char	*srcs;

	if (!(src) && (!(dst)))
		return ((void*)0);
	dest = dst;
	srcs = src;
	ft_mover(dest, srcs, len);
	return (dst);
}
