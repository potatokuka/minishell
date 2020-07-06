/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_re_organize.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 16:52:43 by greed         #+#    #+#                 */
/*   Updated: 2020/07/06 14:11:46 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*save_in_flag(t_input *inp, t_cmd *new, int i)
{
	if (!inp->argv[i + 1])
		put_error("could not find newline");
	new->pipe = ft_strdup(inp->argv[i]);
	new->tar_file = ft_strdup(inp->argv[i + 1]);
	drop_string(inp, i);
	i += 1;
	drop_string(inp, i);
	inp->argc -= 2;
	new->argv = split_arg_lst(new->arr_list);
	new->next = NULL;
	inp->argv = inp->argv + i + 1;
	return (new);
}

static t_cmd	*save_in_pipe(t_input *inp, t_cmd *new, int i)
{
	new->pipe = ft_strdup(inp->argv[i]);
	drop_string(inp, i);
	print_list(new->arr_list);
	new->argv = split_arg_lst(new->arr_list);
	inp->argc -= 1;
	new->next = NULL;
	inp->argv = inp->argv + i + 1;
	return (new);
}

static t_cmd	*split_init(t_input *inp)
{
	t_cmd	*new;
	int		i;

	new = ft_calloc(sizeof(t_cmd), 1);
	i = 0;
	if (!new)
		return (NULL);
	while (inp->argc > 0)
	{
		if (is_cmd(inp->argv[i]))
		{
			new->builtin = ft_strdup(inp->argv[i]);
			drop_string(inp, i);
			inp->argc -= 1;
		}
		else if (inp->argv[i][0] == '|' || inp->argv[i][0] == ';')
		{
			new = save_in_pipe(inp, new, i);
			return (new);
		}
		else if (inp->argv[i][0] == '<' || inp->argv[i][0] == '>')
		{
			new = save_in_flag(inp, new, i);
			return (new);
		}
		else
		{
			lst_new_back(&new->arr_list, ft_strdup(inp->argv[i]));
			new->argc += 1;
			inp->argc -= 1;
			drop_string(inp, i);
		}
		i++;
	}
	if (new->arr_list && !new->pipe)
		new->argv = split_arg_lst(new->arr_list);
	new->next = NULL;
	inp->argv = inp->argv + i;
	return (new);
}

static int		cmd_head_init(t_input *inp, char **argv)
{
	inp->cmd = NULL;
	if (!argv || !argv[0])
		return (-1);
	inp->cmd = split_init(inp);
	if (!inp->cmd)
		return (clear_cmd(inp->cmd, &free));
	return (-1);
}

/*
** now that inp->argv is in a 2d array, now split into cmd structs for each
** cmd given splitting in new cmds on each pipe
** count through for a pipe store if found check argv for a builtin
** save the builtin, and the rest of the argv UNTIL the pipe to the struct
** if REDIR save NEXT argv to tar_file, imp->cmd->next
*/

int				parse_organize(t_input *inp)
{
	t_cmd	*cmd;
	int		i;
	int		n;

	i = cmd_head_init(inp, inp->argv);
	n = 0;
	if (i != -1)
		return (i);
	i = 1;
	cmd = inp->cmd;
	while (inp->argc > 0)
	{
		n++;
		cmd->next = split_init(inp);
		if (!cmd->next)
			return (clear_cmd(inp->cmd, &free));
		cmd = cmd->next;
	}
	print_cmd_full(inp);
	return (0);
}
