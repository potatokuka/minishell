/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ultilities2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 13:45:12 by greed         #+#    #+#                 */
/*   Updated: 2020/10/13 13:45:13 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_3strjoin(const char *str1, const char *str2,
			const char *str3)
{
	char	*combined;

	if (!str1 || !str2 || !str3)
		return (NULL);
	combined = (char *)ft_calloc(ft_strlen_lib(str1) + ft_strlen_lib(str2)
			+ ft_strlen_lib(str3) + 1, sizeof(char));
	if (!combined)
		return (NULL);
	ft_strlcpy_lib(combined, str1, ft_strlen_lib(str1) + 1);
	ft_strlcpy_lib(combined + ft_strlen_lib(str1), str2,
			ft_strlen_lib(str2) + 1);
	ft_strlcpy_lib(combined + ft_strlen_lib(str1) + ft_strlen_lib(str2),
			str3, ft_strlen_lib(str3) + 1);
	return (combined);
}

void	reset_data(t_data *data)
{
	if (data->argv)
		data->argv = (void *)0;
	data->argc = 0;
	data->arg_lst = (void *)0;
	data->cmd = (void *)0;
	return ;
}

int		error_builtin(t_cmd *cmd, int error)
{
	ft_printf_fd(2, "cd: %s: %s\n", cmd->argv[0], strerror(errno));
	return (error);
}

void	ft_free(void **free_me)
{
	if (*free_me)
	{
		free(*free_me);
		*free_me = (void *)0;
	}
}

void	free_fd(t_fd_sto *fd)
{
	if (fd->arr)
		ft_free((void **)&fd->arr);
}
