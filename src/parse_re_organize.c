/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_re_organize.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 16:52:43 by greed         #+#    #+#                 */
/*   Updated: 2020/09/30 15:33:48 by averheij      ########   odam.nl         */
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
	free(tmp);
	dprintf(2, "Test RET_%s\n", ret);
	lst_new_back(&new->arr_list, ft_strdup(ret));
	free(tmp);
	new->argc += 1;
	data->argc -= 1;
	drop_string(data, index);
}

static t_cmd	*save_in_flag(t_data *data, t_cmd *new, int i)
{

	if (!data->argv[i + 1])
		put_error("could not find target file");
	dprintf(2, "saving redirect %s %s\n", data->argv[i], data->argv[i+1]);
	new->tar_file = ft_strdup(data->argv[i + 1]);
	redir_dispatch(&data->fd, new, data->argv[i]);
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
	open_pipe(&data->fd, new);
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
	int		x;

	new = ft_calloc(sizeof(t_cmd), 1);
	new->resetfd[IN] = -1;
	new->resetfd[OUT] = -1;
	new->io_fd[IN] = -1;
	new->io_fd[OUT] = -1;
	new->pipe_read_end = -1;
	i = 0;
	if (!new)
		return (NULL);
	dprintf(2, "Split init Arg Structure:\n");
	while (data->argc > 0)
	{
		x = 0;
		dprintf(2, "%s\n", data->argv[i]);
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
		else if (data->argv[i] && has_escape(data->argv[i]))
		{
			perror("uWu");
			convert_esc(data, new, data->argv[i], i);
			dprintf(2, "ARGC %d\n", data->argc);
			if (data->argc < 1)
				break;
				/* return (new); */
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
	if (new->arr_list && (new->io_fd[IN] == -1 && new->io_fd[OUT] == -1))
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

	/*dprintf(2, "argc%d\n", data->cmd->argc);*/
	/*n = 0;*/
	/*while (n < data->cmd->argc)*/
	/*{*/
		/*dprintf(2, "arg[%d]_%s\n", n, data->cmd->argv[n]);*/
		/*n++;*/
	/*}*/

	n = 0;
	if (i != -1)
		return (i);
	i = 1;
	cmd = data->cmd;
	while (data->argc > 0)
	{
		n++;
		cmd->next = split_init(data);

		/*i = 0;*/
		/*dprintf(2, "argc%d\n", cmd->next->argc);*/
		/*while (i < cmd->next->argc)*/
		/*{*/
			/*dprintf(2, "arg[%d]_%s\n", i, cmd->next->argv[i]);*/
			/*i++;*/
		/*}*/

		if (!cmd->next)
			return (clear_cmd(data->cmd, &free));
		cmd = cmd->next;
	}
	perror("hello");
	print_cmd_full(data);
	return (0);
}
