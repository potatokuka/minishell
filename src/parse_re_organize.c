/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_re_organize.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 16:52:43 by greed         #+#    #+#                 */
/*   Updated: 2020/10/13 12:02:03 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int				has_escape(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}

void			convert_esc(t_data *data, t_cmd *new, char *arg, int index)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	dprintf(2, "Arg= %s\n", arg);
	tmp = ft_calloc(ft_strlen_lib(arg), sizeof(char));
	if (!tmp)
		put_error_data(data, "Allocation Failed 2");
	while (arg[i])
	{
		dprintf(2, "testing arg[i] %c\n", arg[i]);
		if (arg[i] == '\\')
		{
			dprintf(2, "arg check again %s char %c\n", arg, arg[i]);
			tmp[x] = arg[i + 1];
			i += 2;
			x++;
		}
		else
		{
			tmp[x] = arg[i];
			x++;
			i++;
		}
	}
	ret = ft_strldup(tmp, x);
	if (!ret)
		put_error_data(data, "Allocation Failed !");
	free(tmp);
	dprintf(2, "Test RET_%s\n", ret);
	if (!lst_new_back(&new->arr_list, ft_strdup(ret)))
		put_error_data(data, "Failed Allocation in lst back Parse Re");
	free(tmp);
	new->argc += 1;
	data->argc -= 1;
	drop_string(data, index);
}

static t_cmd	*save_in_flag(t_data *data, t_cmd *new, int i)
{

	if (!data->argv[i + 1])
		put_error_data(data, "could not find target file");
	dprintf(2, "saving redirect %s %s\n", data->argv[i], data->argv[i+1]);
	new->tar_file = ft_strdup(data->argv[i + 1]);
	if (!new->tar_file)
		put_error_data(data, "Failed to allocate");//Would leak new?LEAKS
	redir_dispatch(&data->fd, new, data->argv[i]);
	drop_string(data, i);
	i += 1;
	drop_string(data, i);
	data->argc -= 2;
	/* new->argv = list_to_string_array(new->arr_list); */
	/* new->next = NULL; */
	return (new);
}

static t_cmd	*save_in_semi(t_data *data, t_cmd *new, int i)
{
	/*dprintf(2, "saving semicolon %s \n", data->argv[i]);*/
	drop_string(data, i);
	new->argv = list_to_string_array(new->arr_list);
	if (!new->argv)
		put_error_data(data, "Failed to Allocate Lst in Split Init");
	data->argc -= 1;
	new->next = NULL;
	data->argv = data->argv + i + 1;
	return (new);
}

static t_cmd	*save_in_pipe(t_data *data, t_cmd *new, int i)
{
	/*dprintf(2, "saving pipe %s \n", data->argv[i]);*/
	//Check if there is already a redir of STDOUT or STDIN open if so, create pipe but don't assign the already used end
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

static t_cmd	*split_init(t_data *data)
{
	t_cmd	*new;
	int		i;
	int		x;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		put_error_data(data, "Failed to allocate in new cmd struct");
	new->resetfd[IN] = -1;
	new->resetfd[OUT] = -1;
	new->io_fd[IN] = -1;
	new->io_fd[OUT] = -1;
	new->pipe_read_end = -1;
	i = 0;
	dprintf(2, "Split init Arg Structure:\n");
	while (data->argc > 0)
	{
		x = 0;
		dprintf(2, "%s\n", data->argv[i]);
		if (new->argc == 0 && is_builtin(data->argv[0]))
		{
			new->builtin = ft_strdup(data->argv[i]);
			if (!new->builtin)
			{
				free(new);
				put_error_data(data, "Failed to allocate in New Builtin");
			}
			drop_string(data, i);
			data->argc -= 1;
		}
		else if (data->argv[i] && (data->argv[i][0] == '|'))
		{
			if (data->argc == 1)
			{
				free(new);
				reset_prompt(data, "Trailing pipe", 1, 0);
				return (NULL);
			}
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
			if (!lst_new_back(&new->arr_list, ft_strdup(data->argv[i])))
			{
				free(new);
				put_error_data(data, "Failed to Allocate in Lst Back Split init");
			}
			new->argc += 1;
			data->argc -= 1;
			drop_string(data, i);
		}
		i++;
	}
	if (new->arr_list)
	{
		new->argv = list_to_string_array(new->arr_list);
		if (!new->argv)
		{
			free(new);
			put_error_data(data, "Failed to Allocate in split init");
		}
	}
	new->next = NULL;
	data->argv = data->argv + i;
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
