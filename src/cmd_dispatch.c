/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_dispatch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:40 by greed         #+#    #+#                 */
/*   Updated: 2020/09/30 15:29:17 by averheij      ########   odam.nl         */
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
		waitpid(pid->value[i], &pid->status[i], 0);
		i++;
	}
	ft_free((void **)&pid->value);
	ft_free((void **)&pid->status);
}

void	fork_next_and_pipe(t_cmd *cmd, t_var **env, char **envp, t_pid *pid, t_fd_sto *fd, int is_parent)
{
	int		status;
	int		pid_temp;

	pid_temp = fork();
	if (pid_temp != 0)
		ft_add_pid(pid, pid_temp, status);
	if (pid_temp < 0)
		put_error("No Redir Exec Fork Error");
	if (pid_temp == 0)
	{
		ft_reset_pid(pid);
		if (cmd->next->io_fd[IN] == -1)
		{
			cmd->next->io_fd[IN] = cmd->pipe_read_end;
		}
		close_fd(fd, cmd->next->io_fd);
		cmd_dispatch(cmd->next, env, envp, pid);
		wait_for_children(pid);
		exit (0);
	}
	else if (is_parent)
	{
		while (cmd->next && cmd->next->pipe_read_end != -1)
		{
			fork_next_and_pipe(cmd->next, env, envp, pid, fd, 0);
			cmd->next = cmd->next->next;
		}
		if (cmd->next)
			cmd->next = cmd->next->next;
		close_fd(fd, cmd->io_fd);
		cmd_dispatch(cmd, env, envp, pid);
		wait_for_children(pid);
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

void	cmd_dispatch(t_cmd *cmd, t_var **env, char **envp, t_pid *pid)
{

	if (cmd->io_fd[IN] != -1 || cmd->io_fd[OUT] != -1)
		dup_redir(cmd);
	if (cmd->builtin)
	{
		if (ft_strncmp(cmd->builtin, "exit", 4) == 0)
			ft_exit();
		else if (ft_strncmp(cmd->builtin, "echo", 4) == 0)
			ft_echo(cmd);
		else if (ft_strncmp(cmd->builtin, "env", 3) == 0)
			ft_env(envp);
		else if (ft_strncmp(cmd->builtin, "pwd", 3) == 0)
			ft_pwd();
		else if (ft_strncmp(cmd->builtin, "cd", 2) == 0)
			ft_cd(cmd, *env);
		else if (ft_strncmp(cmd->builtin, "unset", 5) == 0)
			ft_unset(cmd, env);
		else if (ft_strncmp(cmd->builtin, "export", 6) == 0)
			ft_export(cmd, env, envp);
	}
	else
		ft_exec(cmd, *env, envp, pid);
	if (cmd->io_fd[IN] != -1 || cmd->io_fd[OUT] != -1)
		close_the_shit(cmd);
}
