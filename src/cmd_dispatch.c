/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_dispatch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:40 by greed         #+#    #+#                 */
/*   Updated: 2020/10/05 17:46:05 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(t_pid *pid)
{
	int i;

	i = 0;
	while (i < pid->count)
	{
		dprintf(2, "[%d]_%d\n", i, pid->value[i]);
		i++;
	}
	i = 0;
	while (i < pid->count)
	{
		dprintf(2, "waiting pid:%d\n", pid->value[i]);
		waitpid(pid->value[i], &pid->last_status, 0);
		dprintf(2, "exited with:%d\n", pid->last_status);
		i++;
	}
	ft_free((void **)&pid->value);
	pid->count = 0;
}

void	fork_next_and_pipe(t_data *data, int is_parent)
{
	int		status;
	int		pid_temp;

	pid_temp = fork();
	if (pid_temp != 0)
		ft_add_pid(&data->pid, pid_temp, status);
	if (pid_temp < 0)
		put_error("No Redir Exec Fork Error");
	if (pid_temp == 0)
	{
		free_pid(&data->pid);
		if (data->cmd->next->io_fd[IN] == -1)
		{
			data->cmd->next->io_fd[IN] = data->cmd->pipe_read_end;
		}
		close_fd(&data->fd, data->cmd->next->io_fd);
		cmd_dispatch(data);
		wait_for_children(&data->pid);
		exit (0);
	}
	else if (is_parent)
	{
		while (data->cmd->next && data->cmd->next->pipe_read_end != -1)
		{
			fork_next_and_pipe(data, 0);
			data->cmd->next = data->cmd->next->next;
		}
		if (data->cmd->next)
			data->cmd->next = data->cmd->next->next;
		close_fd(&data->fd, data->cmd->io_fd);
		cmd_dispatch(data);
	}
}

void	close_the_shit(t_cmd *cmd)
{
	if (cmd->resetfd[IN] != -1)
	{
		if (dup2(cmd->resetfd[IN], STDIN_FILENO) == -1)
			put_error("Failed to reset STDIN");
		close(cmd->resetfd[IN]);
		cmd->resetfd[IN] = -1;
	}
	if (cmd->resetfd[OUT] != -1)
	{
		if (dup2(cmd->resetfd[OUT], STDOUT_FILENO) == -1)
			put_error("Failed to reset STDIN");
		close(cmd->resetfd[OUT]);
		cmd->resetfd[OUT] = -1;

	}
	if (cmd->io_fd[IN] != -1)
		close(cmd->io_fd[IN]);
	if (cmd->io_fd[OUT] != -1)
		close(cmd->io_fd[OUT]);
}

void	dup_redir(t_cmd *cmd)
{
	if (cmd->io_fd[IN] != -1)
	{
		cmd->resetfd[IN] = dup(STDIN);
		dprintf(2, "Dup2 FD in : %d\n", cmd->io_fd[IN]);
		if (cmd->io_fd[IN] != -1 &&
				dup2(cmd->io_fd[IN], STDIN_FILENO) == -1)
			put_error("Failed to dup STDIN");
		if (cmd->io_fd[IN] != -1)
			close(cmd->io_fd[IN]);
	}
	if (cmd->io_fd[OUT] != -1)
	{
		cmd->resetfd[OUT] = dup(STDOUT);
		dprintf(2, "Dup2 FD out : %d\n", cmd->io_fd[OUT]);
		if (cmd->io_fd[OUT] != -1 &&
					dup2(cmd->io_fd[OUT], STDOUT_FILENO) == -1)
			put_error("Failed to dup STDOUT");
		if (cmd->io_fd[OUT] != -1)
			close(cmd->io_fd[OUT]);
	}
}

void	cmd_dispatch(t_data *data)
{
	if (data->cmd->io_fd[IN] != -1 || data->cmd->io_fd[OUT] != -1)
		dup_redir(data->cmd);
	if (data->cmd->builtin)
	{
		if (ft_strncmp(data->cmd->builtin, "exit", 4) == 0)
			ft_exit();
		else if (ft_strncmp(data->cmd->builtin, "echo", 4) == 0)
			ft_echo(data->cmd);
		else if (ft_strncmp(data->cmd->builtin, "env", 3) == 0)
			ft_env(data->envp);
		else if (ft_strncmp(data->cmd->builtin, "pwd", 3) == 0)
			data->pid.last_status = ft_pwd();
		else if (ft_strncmp(data->cmd->builtin, "cd", 2) == 0)
			data->pid.last_status = ft_cd(data->cmd, data->env);
		else if (ft_strncmp(data->cmd->builtin, "unset", 5) == 0)
			ft_unset(data->cmd, &data->env);
		else if (ft_strncmp(data->cmd->builtin, "export", 6) == 0)
			ft_export(data->cmd, &data->env, data->envp);
	}
	else
		ft_exec(data->cmd, data->env, data->envp, &data->pid);
	if (data->cmd->io_fd[IN] != -1 || data->cmd->io_fd[OUT] != -1)
		close_the_shit(data->cmd);
}
