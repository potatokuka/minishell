#include "minishell.h"


// -DATA-
// argv - arg_lst - pid - fd - envp
// env - cmd - redirs
//
// free the arrays if its a struct free the struct
// free the shit that's malloc, (*) then free the fucking
// struct

void		free_fd(t_fd_sto *fd)
{
	if (fd->arr)
		ft_free((void **)&fd->arr);
}

void		free_var(t_var *env)
{
	if (env->name)
		ft_free((void **)&env->name);
	if (env->val)
		ft_free((void **)&env->val);
	if (env->next && env->next != NULL)
		free_var(env->next);
	ft_free((void **)&env);
}

void		free_pid(t_pid *pid)
{
	if (pid->value)
		ft_free((void **)&pid->value);
	if (pid->status)
		ft_free((void **)pid->status);
}

void		free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->builtin)
		ft_free((void **)&cmd->builtin);
	if (cmd->argv)
	{
		free_array_null(cmd->argv);
		ft_free((void **)&cmd->argv);
	}
	if (cmd->tar_file)
		ft_free((void **)&cmd->tar_file);
	if (cmd->arr_list)
	{
		free_list(cmd->arr_list, free);
		ft_free((void **)&cmd->arr_list);
	}
	if (cmd->next && cmd->next != NULL)
		free_cmd(cmd->next);
	free(cmd);
}

void		reset_data_struct(t_data *data)
{
	if (!data)
		return ;
	if (data->cmd)
	{
		free_cmd(data->cmd);
		data->cmd = NULL;
	}
	if (data->arg_lst)
	{
		free_list(data->arg_lst, free);
		data->arg_lst = NULL;
	}
	free_pid(&data->pid);
	if (data->env)
	{
		free_var(data->env);
		ft_free((void **)&data->env);
	}
	free_fd(&data->fd);
	if (data->envp)
		free_array_null(data->envp);
}

void		error_reset(t_data *data, char *error)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	reset_data_struct(data);
}
