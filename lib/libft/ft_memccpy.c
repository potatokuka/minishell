/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:50:17 by greed         #+#    #+#                 */
/*   Updated: 2019/11/06 14:46:35 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		i;
	char		*ptr;
	char		*dest;
	const char	*srcs;

	i = 0;
	ptr = 0;
	dest = dst;
	srcs = src;
	while (i < n)
	{
		dest[i] = srcs[i];
		if ((unsigned char)srcs[i] == (unsigned char)c)
		{
			ptr = &dest[i + 1];
			break ;
		}
		i++;
	}
	return (ptr);
}
