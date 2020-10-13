/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/20 12:41:15 by greed         #+#    #+#                 */
/*   Updated: 2020/10/13 17:52:55 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Set a storage amount for initial path size, if the path is too large
** Set a larger path size
*/

int		get_path(char **res)
{
	char	*path;
	size_t	size;

	size = 20;
	path = ft_calloc(sizeof(char), (size + 1));
	if (!path)
		return (1);
	*res = getcwd(path, size + 1);
	while (!*res && errno == ERANGE)
	{
		size += 20;
		free(path);
		path = ft_calloc(sizeof(char), (size + 1));
		if (!path)
			return (1);
		*res = getcwd(path, size + 1);
	}
	return (0);
}

int		ft_pwd(void)
{
	char	*path;

	dprintf(2, "inside pwd\n");
	if (get_path(&path))
		return (2);
	if (path)
	{
		ft_printf("%s\n", path);
		free(path);
		return (0);
	}
	else
		return (1);
}
