/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:49 by greed         #+#    #+#                 */
/*   Updated: 2020/10/08 12:58:18 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** count the len unti it reaches the sent char
*/

int		ft_add_pid(t_pid *pid, int add_value)
{
	int		i;
	int		*tmp_value;
	t_pid	tmp;

	dprintf(2, "adding child pid:%d\n", add_value);
	tmp_value = ft_calloc(sizeof(int), pid->count + 2);
	if (!tmp_value)
		return (1);
	i = 0;
	while (i < pid->count)
	{
		tmp_value[i] = pid->value[i];
		i++;
	}
	pid->count += 1;
	tmp_value[i] = add_value;
	ft_free((void **)&pid->value);
	pid->value = tmp_value;
	return (0);
}

int		ft_is_redir(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (1);
	else
		return (0);
}
size_t	ft_strclen(const char *str, int c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

char	*ft_3strjoin(const char *str1, const char *str2,
			const char *str3)
{
	// PROBABLY HERE!
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
	return(combined);
}

void	reset_data(t_data *data)
{
	if (data->argv)
		data->argv = (void *)0;
		/*free_array_null(data->argv);*/
	data->argc = 0;
	/*if (data->redirs)*/
		/*free_array_null(data->redirs);*/
	data->arg_lst = (void *)0;
	data->cmd = (void *)0;
	return ;
}

int 	error_builtin(t_cmd *cmd, int error)
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
