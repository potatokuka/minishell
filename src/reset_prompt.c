/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_prompt.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 12:44:28 by greed         #+#    #+#                 */
/*   Updated: 2020/10/28 15:04:34 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_data2(t_data *data, int all)
{
	int	i;

	i = 0;
	free_pid(&data->pid);
	if (all == 1 && data->env)
	{
		free_var(data->env);
		data->env = NULL;
	}
	while (i < data->fd.used)
	{
		close(data->fd.arr[i]);
		i++;
	}
	free_fd(&data->fd);
	if (data->envp)
		data->envp = free_array_null(data->envp);
}

void		free_pid(t_pid *pid)
{
	pid->count = 0;
	if (pid->value)
		ft_free((void **)&pid->value);
}

void		free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->builtin)
		ft_free((void **)&cmd->builtin);
	if (cmd->argv)
		cmd->argv = free_array_null(cmd->argv);
	if (cmd->tar_file)
		ft_free((void **)&cmd->tar_file);
	if (cmd->arr_list)
	{
		free_list(cmd->arr_list, free);
		cmd->arr_list = (t_list *)0;
	}
	if (cmd->next && cmd->next != NULL)
		free_cmd(cmd->next);
	free(cmd);
}

void		reset_data_struct(t_data *data, int all)
{
	if (!data)
		return ;
	free_data_argv(data);
	if (data->cmd)
	{
		free_cmd(data->cmd);
		data->cmd = NULL;
	}
	if (data->forked)
	{
		free_cmd(data->forked);
		data->forked = NULL;
	}
	if (data->arg_lst)
	{
		free_list(data->arg_lst, free);
		data->arg_lst = NULL;
	}
	close_fd(&data->fd, NULL);
	free_data2(data, all);
}

int			reset_prompt(t_data *data, char *error, int error_status, int all)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	data->pid.last_status = error_status;
	if (data->input_leftovers)
	{
		free(data->input_head);
		data->input_leftovers = NULL;
	}
	reset_data_struct(data, all);
	return (error_status);
}
