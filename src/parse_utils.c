/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 20:45:35 by greed         #+#    #+#                 */
/*   Updated: 2020/10/13 14:04:03 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				clear_cmd(t_cmd *cmd, void(*del)(void *))
{
	t_cmd	*delete;

	while (cmd)
	{
		delete = cmd;
		cmd = cmd->next;
		if (delete->builtin)
			del(delete->builtin);
		if (delete->tar_file)
			del(delete->tar_file);
		if (delete->argv)
			free_array_null(delete->argv);
	}
	return (1);
}

int		drop_string(t_data *data, int i)
{
	if (data->argv[i])
		free(data->argv[i]);
	data->argv[i] = NULL;
	return (0);
}
