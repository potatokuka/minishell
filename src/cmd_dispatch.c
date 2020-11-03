/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_dispatch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:40 by greed         #+#    #+#                 */
/*   Updated: 2020/11/03 12:05:09 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			wait_for_children(t_pid *pid, int parent_exec)
{
	int i;
	int	temp;

	i = 0;
	while (i < pid->count)
	{
		waitpid(pid->value[i], &temp, 0);
		if (!(parent_exec && i == pid->count - 1 && pid->count > 1))
			pid->last_status = temp / 256;
		i++;
	}
	ft_free((void **)&pid->value);
	pid->count = 0;
}

static void		child_process(t_data *data, t_cmd *cmd)
{
	g_is_parent = 0;
	free_pid(&data->pid);
	if (cmd->next->io_fd[IN] == -1)
		cmd->next->io_fd[IN] = cmd->pipe_read_end;
	close_fd(&data->fd, cmd->next->io_fd);
	cmd_dispatch(data, cmd->next, 1);
	wait_for_children(&data->pid, 0);
	reset_data_struct(data, 1);
	exit(data->pid.last_status);
}

void			fork_next_and_pipe(t_data *data, t_cmd *cmd, int is_parent)
{
	int		pid_temp;

	pid_temp = fork();
	if (pid_temp != 0)
		if (ft_add_pid(&data->pid, pid_temp))
			put_error_data(data, "Failed to add pid");
	if (pid_temp < 0)
		put_error_data(data, "Failed to Fork Redirection");
	if (pid_temp == 0)
		child_process(data, cmd);
	else if (is_parent)
	{
		while (cmd->next && cmd->next->pipe_read_end != -1)
		{
			fork_next_and_pipe(data, cmd->next, 0);
			cmd->next = add_forked_cmd(data, cmd->next);
		}
		if (cmd->next)
			cmd->next = add_forked_cmd(data, cmd->next);
		close_fd(&data->fd, cmd->io_fd);
		cmd_dispatch(data, cmd, 0);
	}
}

int				close_the_shit(t_cmd *cmd)
{
	if (cmd->resetfd[IN] != -1)
	{
		if (dup2(cmd->resetfd[IN], STDIN_FILENO) == -1)
			return (1);
		close(cmd->resetfd[IN]);
		cmd->resetfd[IN] = -1;
	}
	if (cmd->resetfd[OUT] != -1)
	{
		if (dup2(cmd->resetfd[OUT], STDOUT_FILENO) == -1)
			return (1);
		close(cmd->resetfd[OUT]);
		cmd->resetfd[OUT] = -1;
	}
	if (cmd->io_fd[IN] != -1)
		close(cmd->io_fd[IN]);
	if (cmd->io_fd[OUT] != -1)
		close(cmd->io_fd[OUT]);
	return (0);
}

void			cmd_dispatch(t_data *data, t_cmd *cmd, int is_child)
{
	if (dup_redir(cmd, is_child))
		put_error_data(data, "Failed to dup Redir");
	if (cmd->builtin)
	{
		if (ft_strncmp(cmd->builtin, "exit", 4) == 0)
			data->pid.last_status = ft_exit(cmd, data->pid.last_status);
		else if (ft_strncmp(cmd->builtin, "echo", 4) == 0)
			ft_echo(cmd);
		else if (ft_strncmp(cmd->builtin, "env", 3) == 0)
			ft_env(data->envp);
		else if (ft_strncmp(cmd->builtin, "pwd", 3) == 0)
			data->pid.last_status = ft_pwd();
		else if (ft_strncmp(cmd->builtin, "cd", 2) == 0)
			data->pid.last_status = ft_cd(cmd, data->env);
		else if (ft_strncmp(cmd->builtin, "unset", 5) == 0)
			data->pid.last_status = ft_unset(cmd, &data->env);
		else if (ft_strncmp(cmd->builtin, "export", 6) == 0)
			data->pid.last_status = ft_export(cmd, &data->env, data->envp);
		if (data->pid.last_status == 2)
			put_error_data(data, "Builtin fatal error");
	}
	else
		data->pid.last_status = ft_exec(cmd, data->env, data->envp, &data->pid);
	if (close_the_shit(cmd))
		put_error_data(data, "Failed to reset STDIN, STDOUT");
}
