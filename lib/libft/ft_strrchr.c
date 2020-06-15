/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 12:30:37 by greed         #+#    #+#                 */
/*   Updated: 2019/11/06 10:30:59 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			tmp = (char*)&s[i];
		i++;
	}
	if (s[i] == (char)c)
		tmp = ((char*)&s[i]);
	return (tmp);
}
