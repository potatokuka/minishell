/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 09:07:10 by greed         #+#    #+#                 */
/*   Updated: 2019/12/07 12:59:14 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_substr_lib(char const *s, unsigned int start, size_t len)
{
	size_t				i;
	char				*dst;
	unsigned int		tmp;

	i = 0;
	if (!(s))
		return (NULL);
	tmp = ft_strlen_lib(s);
	if (start > tmp)
		return (ft_strdup_lib(""));
	dst = (char*)malloc(len + 1);
	if (!(dst))
		return (NULL);
	while (i < len)
	{
		dst[i] = s[start];
		start++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
