/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 16:26:58 by greed         #+#    #+#                 */
/*   Updated: 2019/11/06 14:47:12 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*ptr;
	const char	*str;

	i = 0;
	ptr = 0;
	str = s;
	while (i < n)
	{
		if (str[i] == c)
		{
			ptr = &str[i];
			break ;
		}
		i++;
	}
	return ((char*)ptr);
}
