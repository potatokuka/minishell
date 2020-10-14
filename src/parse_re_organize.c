/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_re_organize.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 16:52:43 by greed         #+#    #+#                 */
/*   Updated: 2020/10/14 12:52:57 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_cmd			*save_in_flag(t_data *data, t_cmd *new, int i)
{
	if (!data->argv[i + 1])
		put_error_data(data, "could not find target file");
	new->tar_file = ft_strdup(data->argv[i + 1]);
	if (!new->tar_file)
		put_error_data(data, "Failed to allocate");
	redir_dispatch(&data->fd, new, data->argv[i]);
	drop_string(data, i);
	i += 1;
	drop_string(data, i);
	data->argc -= 2;
	return (new);
}

t_cmd			*save_in_semi(t_data *data, t_cmd *new, int i)
{
	drop_string(data, i);
	new->argv = list_to_string_array(new->arr_list);
	if (!new->argv)
		put_error_data(data, "Failed to Allocate Lst in Split Init");
	data->argc -= 1;
	new->next = NULL;
	data->argv = data->argv + i + 1;
	return (new);
}

t_cmd			*save_in_pipe(t_data *data, t_cmd *new, int i)
{
	if (data->argc == 1)
	{
		free(new);
		reset_prompt(data, "Trailing pipe", 1, 0);
		return (NULL);
	}
	if (open_pipe(&data->fd, new))
		put_error_data(data, "Failed to Allocate in Open Pipe");
	drop_string(data, i);
	new->argv = list_to_string_array(new->arr_list);
	if (!new->argv)
		put_error_data(data, "Failed to Allocate Lst in Split Init");
	data->argc -= 1;
	new->next = NULL;
	data->argv = data->argv + i + 1;
	return (new);
}

static int		cmd_head_init(t_data *data, char **argv)
{
	data->cmd = NULL;
	if (!argv || !argv[0])
	{
		reset_prompt(data, "", 0, 1);
		return (0);
	}
	data->cmd = split_init(data);
	if (!data->cmd)
		return (clear_cmd(data->cmd, &free));
	return (0);
}

/*
** now that data->argv is in a 2d array, now split into cmd structs for each
** cmd given splitting in new cmds on each pipe
** count through for a pipe store if found check argv for a builtin
** save the builtin, and the rest of the argv UNTIL the pipe to the struct
** if REDIR save NEXT argv to tar_file, imp->cmd->next
*/

int				parse_organize(t_data *data)
{
	t_cmd	*tmp;
	t_cmd	*cmd;
	char	**argvhead;

	argvhead = data->argv;
	if (cmd_head_init(data, data->argv))
		return (1);
	cmd = data->cmd;
	while (data->argc > 0)
	{
		tmp = split_init(data);
		if (!tmp)
			return (clear_cmd(data->cmd, &free));
		cmd->next = tmp;
		cmd = cmd->next;
	}
	if (argvhead)
	{
		free(argvhead);
		data->argv = NULL;
	}
	print_cmd_full(data);
	return (0);
}
