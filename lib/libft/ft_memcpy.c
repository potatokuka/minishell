/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:10:24 by greed         #+#    #+#                 */
/*   Updated: 2019/11/06 14:46:13 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*srcs;

	i = 0;
	dest = dst;
	srcs = src;
	if (src == NULL && dst == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = srcs[i];
		i++;
	}
	return (dst);
}
