/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_re_organize.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 16:52:43 by greed         #+#    #+#                 */
/*   Updated: 2020/09/22 11:04:06 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static t_cmd	*save_in_flag(t_data *data, t_cmd *new, int i)
{
	if (!data->argv[i + 1])
		put_error("could not find newline");
	// ! this is a dumb fix, but maybe a work around.
	// if (data->redir_count > 1)
	// {
	// 	put_error("inside redir count");
	// 	drop_string(data, i);
	// 	i += 1;
	// 	int file = open(data->argv[i], O_RDONLY, 0644);
	// 	close (file);
	// 	drop_string(data, i);
	// 	new->argv = list_to_string_array(new->arr_list);
	// 	new->next = NULL;
	// 	data->redir_count -= 1;
	// 	data->argv = data->argv + i + 1;
	// 	data->argc -= 2;
	// 	return (new);
	// }
	new->pid1 = -1;
	new->pipfd[0] = -1;
	new->pipfd[1] = -1;
	new->pipe = ft_strdup(data->argv[i]);
	drop_string(data, i);
	i += 1;
	new->tar_file = ft_strdup(data->argv[i]);
	drop_string(data, i);
	data->argc -= 2;
	new->argv = list_to_string_array(new->arr_list);
	new->next = NULL;
	data->argv = data->argv + i + 1;
	return (new);
}

static t_cmd	*save_in_pipe(t_data *data, t_cmd *new, int i)
{
	dprintf(2, "checking this input %s \n", data->argv[i]);
	new->pipe = ft_strdup(data->argv[i]);
	drop_string(data, i);
	print_list(new->arr_list);
	if (new->argv)
		dprintf(2, "checking this input %s \n", new->argv[i]);
	new->argv = list_to_string_array(new->arr_list);
	data->argc -= 1;
	new->next = NULL;
	data->argv = data->argv + i + 1;
	return (new);
}

static t_cmd	*split_init(t_data *data)
{
	t_cmd	*new;
	int		i;

	new = ft_calloc(sizeof(t_cmd), 1);
	i = 0;
	if (!new)
		return (NULL);
	while (data->argc > 0)
	{
		if (new->argc == 0 && is_builtin(data->argv[i]))
		{
			new->builtin = ft_strdup(data->argv[i]);
			drop_string(data, i);
			data->argc -= 1;
		}
		else if (data->argv[i][0] == '|' || data->argv[i][0] == ';')
		{
			new = save_in_pipe(data, new, i);
			return (new);
		}
		else if (data->argv[i][0] == '<' || data->argv[i][0] == '>')
		{
			new = save_in_flag(data, new, i);
			return (new);
		}
		else
		{
			lst_new_back(&new->arr_list, ft_strdup(data->argv[i]));
			new->argc += 1;
			data->argc -= 1;
			drop_string(data, i);
		}
		i++;
	}
	if (new->arr_list && !new->pipe)
		new->argv = list_to_string_array(new->arr_list);
	new->next = NULL;
	data->argv = data->argv + i;
	return (new);
}

static int		cmd_head_init(t_data *data, char **argv)
{
	data->cmd = NULL;
	if (!argv || !argv[0])
		return (-1);
	data->cmd = split_init(data);
	if (!data->cmd)
		return (clear_cmd(data->cmd, &free));
	return (-1);
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
	t_cmd	*cmd;
	int		i;
	int		n;

	i = cmd_head_init(data, data->argv);
	n = 0;
	if (i != -1)
		return (i);
	i = 1;
	cmd = data->cmd;
	while (data->argc > 0)
	{
		n++;
		cmd->next = split_init(data);
		if (!cmd->next)
			return (clear_cmd(data->cmd, &free));
		perror("moving cmd->NEXT in PARSE ORGANIZE");
		cmd = cmd->next;
	}
	dprintf(2, "This is b4 print_cmd_full\n");
	print_cmd_full(data);
	return (0);
}
