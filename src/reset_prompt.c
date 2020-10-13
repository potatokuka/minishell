/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_prompt.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 12:44:28 by greed         #+#    #+#                 */
/*   Updated: 2020/10/12 15:33:53 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_fd(t_fd_sto *fd)
{
	if (fd->arr)
		ft_free((void **)&fd->arr);
}

void		free_var(t_var *env)
{
	if (!env)
		return ;
	if (env->name)
		ft_free((void **)&env->name);
	if (env->val)
		ft_free((void **)&env->val);
	if (env->next && env->next != NULL)
		free_var(env->next);
	free(env);
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
	data->argc = 0;
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
	free_pid(&data->pid);
	if (all == 1 && data->env)
	{
		free_var(data->env);
		data->env = NULL;
	}
	free_fd(&data->fd);
	if (data->envp)
		data->envp = free_array_null(data->envp);
}

int		reset_prompt(t_data *data, char *error, int error_status, int all)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	data->pid.last_status = error_status;
	reset_data_struct(data, all);
	return (error_status);
}
