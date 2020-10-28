/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 14:03:31 by greed         #+#    #+#                 */
/*   Updated: 2020/10/28 14:03:32 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	char	*new;

	new = (char *)ft_calloc(1, new_size);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (new);
	ft_memcpy(new, ptr, old_size);
	free(ptr);
	return (new);
}
