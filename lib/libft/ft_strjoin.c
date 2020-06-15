/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 09:45:17 by greed         #+#    #+#                 */
/*   Updated: 2019/12/07 13:03:17 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_dubstrlen(const char *str1, const char *str2)
{
	int len1;
	int len2;
	int totlen;

	len1 = 0;
	len2 = 0;
	while (str1[len1] != '\0')
	{
		len1++;
	}
	while (str2[len2] != '\0')
	{
		len2++;
	}
	totlen = len1 + len2;
	return (totlen);
}

static char		*ft_dubcpy(char *dest, char const *s1, char const *s2, size_t j)
{
	size_t i;

	i = 0;
	while (s1[j])
	{
		dest[j] = s1[j];
		j++;
	}
	while (s2[i])
	{
		dest[j] = s2[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

char			*ft_strjoin_lib(char const *s1, char const *s2)
{
	void		*stored;
	char		*dst;
	size_t		i;
	size_t		j;

	j = 0;
	if (s1 == 0)
		return (NULL);
	i = ft_dubstrlen(s1, s2);
	stored = (void*)ft_calloc(sizeof(char), i + j);
	if (!(stored))
		return (NULL);
	dst = (char*)malloc(i + j + 1);
	i = 0;
	ft_dubcpy(dst, s1, s2, j);
	return (dst);
}
