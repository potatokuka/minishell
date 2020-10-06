/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 12:41:15 by greed         #+#    #+#                 */
/*   Updated: 2020/09/18 18:11:21 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Set a storage amount for initial path size, if the path is too large
** Set a larger path size
*/

char	*get_path(void)
{
	char	*res;
	char	*path;
	size_t	size;

	size = 20;
	path = ft_calloc(sizeof(char), (size + 1));
	if (!path)
		put_error("Error getting path");
	res = getcwd(path, size + 1);
	while (!res && errno == ERANGE)
	{
		size += 20;
		free(path);
		path = ft_calloc(sizeof(char), (size + 1));
		if (!path)
			put_error("Error getting path");
		res = getcwd(path, size + 1);
	}
	return (res);
}

int	ft_pwd(void)
{
	char	*path;

	dprintf(2,"inside pwd\n");
	path = get_path();
	if (path)
	{
		ft_printf("%s\n", path);
		free(path);
		return (0);
	}
	else
		return (1);
}
