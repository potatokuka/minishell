/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 10:05:57 by greed         #+#    #+#                 */
/*   Updated: 2019/12/07 12:03:15 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_lib(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char*)&s[i]);
		i++;
	}
	if (s[i] == (char)(c))
		return ((char*)&s[i]);
	return (NULL);
}
