/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_update.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/22 23:10:18 by greed         #+#    #+#                 */
/*   Updated: 2020/10/08 12:05:15 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_array_null(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

void	update_env(t_data *data)
{
	// something isnt been freed here.
	if (set_exit_env_val(&data->env, &data->pid.last_status))
		put_error_data(data, "Failed to set $?");
	if (data->envp)
		free_array_null(data->envp);
	data->envp = convert_env(data->env);
	if (!data->envp)
		put_error_data(data, "Failed to convert enviroment");
}
