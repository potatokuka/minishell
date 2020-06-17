/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strldup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 19:55:29 by greed         #+#    #+#                 */
/*   Updated: 2020/06/17 20:02:47 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Duplicate at most n - 1 bytes of src. Always null-terminates the result
**	string. Returns NULL if the allocation fails or when s == null.
*/

char	*ft_strldup(const char *src, size_t n)
{
	size_t	len;
	char	*res;

	if (src == NULL)
		return (NULL);
	len = ft_strlen_lib(src);
	len = (len > n ? n : len) + 1;
	res = (char *)malloc(len);
	if (res == NULL)
		return (NULL);
	ft_strlcpy_lib(res, src, len);
	return (res);
}
