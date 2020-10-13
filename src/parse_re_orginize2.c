/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_re_orginize2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/13 17:26:46 by greed         #+#    #+#                 */
/*   Updated: 2020/10/13 17:28:33 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		split_builtin(t_data *data, t_cmd *new, int i)
{
	new->builtin = ft_strdup(data->argv[i]);
	if (!new->builtin)
		put_error_data_cmd(data, new, "Failed to allocate in New Builtin");
	drop_string(data, i);
	data->argc -= 1;
}

static void		split_init2(t_data *data, t_cmd *new, int i)
{
	if (!lst_new_back(&new->arr_list, ft_strdup(data->argv[i])))
		put_error_data_cmd(data, new, "Failed to Allocate Lst Back");
	new->argc += 1;
	data->argc -= 1;
	drop_string(data, i);
}

static void		new_arr_list(t_data *data, t_cmd *new)
{
	if (new->arr_list)
	{
		new->argv = list_to_string_array(new->arr_list);
		if (!new->argv)
			put_error_data_cmd(data, new, "Failed to Allocate split init");
	}
	new->next = NULL;
}

static t_cmd	*split_new(t_data *data, t_cmd *new)
{
	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		put_error_data(data, "Failed to allocate in new cmd struct");
	new->resetfd[IN] = -1;
	new->resetfd[OUT] = -1;
	new->io_fd[IN] = -1;
	new->io_fd[OUT] = -1;
	new->pipe_read_end = -1;
	return (new);
}

t_cmd	*split_init(t_data *da)
{
	t_cmd	*new;
	int		i;

	new = split_new(da, new);
	i = 0;
	while (da->argc > 0)
	{
		if (new->argc == 0 && is_builtin(da->argv[0]))
			split_builtin(da, new, i);
		else if (da->argv[i] && (da->argv[i][0] == '|'))
			return (save_in_pipe(da, new, i));
		else if (da->argv[i][0] == ';')
			return (save_in_semi(da, new, i));
		else if (da->argv[i] && (da->argv[i][0] == 60 || da->argv[i][0] == 62))
		{
			new = save_in_flag(da, new, i);
			i++;
		}
		else
			split_init2(da, new, i);
		i++;
	}
	new_arr_list(da, new);
	da->argv = da->argv + i;
	return (new);
}
