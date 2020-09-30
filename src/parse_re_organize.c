/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_re_organize.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 16:52:43 by greed         #+#    #+#                 */
/*   Updated: 2020/09/30 10:44:35 by averheij      ########   odam.nl         */
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
	/*dprintf(2, "saving redirect %s %s\n", data->argv[i], data->argv[i+1]);*/
	new->tar_file = ft_strdup(data->argv[i + 1]);
	redir_dispatch(new, data->argv[i]);
	drop_string(data, i);
	i += 1;
	drop_string(data, i);
	data->argc -= 2;
	new->argv = list_to_string_array(new->arr_list);
	new->next = NULL;
	return (new);
}

static t_cmd	*save_in_semi(t_data *data, t_cmd *new, int i)
{
	/*dprintf(2, "saving semicolon %s \n", data->argv[i]);*/
	drop_string(data, i);
	new->argv = list_to_string_array(new->arr_list);
	data->argc -= 1;
	new->next = NULL;
	data->argv = data->argv + i + 1;
	return (new);
}

static t_cmd	*save_in_pipe(t_data *data, t_cmd *new, int i)
{
	/*dprintf(2, "saving pipe %s \n", data->argv[i]);*/
	//Check if there is already a redir of STDOUT or STDIN open if so, create pipe but don't assign the already used end
	open_pipe(new);
	drop_string(data, i);
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
	new->resetfd[IN] = -1;
	new->resetfd[OUT] = -1;
	new->pipfd[IN] = -1;
	new->pipfd[OUT] = -1;
	new->pipfd2[READ_FD] = -1;
	new->pipfd2[WRITE_FD] = -1;
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
		else if (data->argv[i] && (data->argv[i][0] == '|'))
		{
			new = save_in_pipe(data, new, i);
			return (new);
		}
		else if (data->argv[i][0] == ';')
		{
			new = save_in_semi(data, new, i);
			return (new);
		}
		else if (data->argv[i] && (data->argv[i][0] == '<' || data->argv[i][0] == '>'))
		{
			new = save_in_flag(data, new, i);
			i++;
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
	if (new->arr_list && (new->pipfd[IN] == -1 && new->pipfd[OUT] == -1))
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
		cmd = cmd->next;
	}
	print_cmd_full(data);
	return (0);
}
