/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 15:51:34 by greed         #+#    #+#                 */
/*   Updated: 2020/05/20 13:49:37 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <errno.h>

char	*ft_strdup_lib(const char *s1)
{
	int				len;
	int				i;
	char			*str;

	len = 0;
	i = 0;
	while (s1[len])
		len++;
	str = (char*)malloc(len + 1);
	if (!str)
		ENOMEM;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
