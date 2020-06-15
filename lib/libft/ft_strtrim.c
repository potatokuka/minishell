/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 10:26:02 by greed         #+#    #+#                 */
/*   Updated: 2019/12/07 13:04:31 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	in_set(const char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	char	*beg;
	char	*end;

	if (s1 == 0)
		return (NULL);
	beg = (char*)s1;
	end = (char*)s1 + ft_strlen_lib(s1) - 1;
	while (in_set(set, *beg))
		beg++;
	while (in_set(set, *end))
		end--;
	end++;
	res = (char*)malloc((beg >= end) ? 1 : (end - beg + 1));
	if (!(res))
		return (NULL);
	if (beg >= end)
		res[0] = '\0';
	else
		ft_strlcpy(res, beg, end - beg + 1);
	return (res);
}
