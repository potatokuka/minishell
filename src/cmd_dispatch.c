/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_dispatch.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 18:05:40 by greed         #+#    #+#                 */
/*   Updated: 2020/09/25 15:04:06 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children(t_pid *pid)
{
	int i = 0;
	/*while (pid->value[i])*/
	while (i < pid->count)
	{
		dprintf(2, "[%d]_%d\n", i, pid->value[i]);
		i++;
	}
	while (pid->count > 0)
	{
		dprintf(2, "waiting pid:%d\n", pid->value[pid->count - 1]);
		waitpid(pid->value[pid->count - 1], &pid->status[pid->count - 1], 0);
		pid->count--;
	}
	ft_free((void **)&pid->value);
	ft_free((void **)&pid->status);
}

void	fork_next_and_pipe(t_cmd *cmd, t_var **env, char **envp, t_pid *pid, int is_parent)
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
		//Closing my duplicate of senders pipe and assigning my read end
		close(cmd->pipfd2[WRITE_FD]);//Does this need protection
		if (cmd->next->pipfd[IN] == -1)
			cmd->next->pipfd[IN] = cmd->pipfd2[READ_FD];

		//Closing my duplicate of recievers pipe and opening my write end
		if (cmd->next->pipfd2[READ_FD] != -1 && cmd->next->pipfd2[WRITE_FD] != -1)
		{
			close(cmd->next->pipfd2[READ_FD]);//Does this need protectoin
			if (cmd->next->pipfd[OUT] == -1)
				cmd->next->pipfd[OUT] = cmd->next->pipfd2[WRITE_FD];
		}

		perror("about to cmd_dispatch this command:");
		print_cur_cmd(cmd->next);
		cmd_dispatch(cmd->next, env, envp, pid);

		//My pipe to my reciever
		if (cmd->next->pipfd2[WRITE_FD] != -1)
			close(cmd->next->pipfd2[WRITE_FD]);//Does this need protectoin
		//My pipe
		close(cmd->pipfd2[READ_FD]);//Does this need protectoin
		perror("end of child process");
		exit (0);
	}
	else if (is_parent)
	{
		while (cmd->next && cmd->next->pipfd2[READ_FD] != -1 && cmd->next->pipfd2[WRITE_FD] != -1)
		{
			perror("forking child from while loop");
			fork_next_and_pipe(cmd->next, env, envp, pid, 0);
			cmd->next = cmd->next->next;
		}
		cmd->next = cmd->next->next;

		close(cmd->pipfd2[READ_FD]);//Does this need protectoin
		if (cmd->pipfd[OUT] == -1)
			cmd->pipfd[OUT] = cmd->pipfd2[WRITE_FD];
		//for multiple pipes i.e. echo fag | cat | cat, try calling the forking from inside here, rather than inside the child

		cmd_dispatch(cmd, env, envp, pid);
		close(cmd->pipfd2[WRITE_FD]);//Does this need protectoin
		// ! waitpid(cmd->pid1, &status, 0);
		//This is intended to skip over every cmd that is going to be forked and piped by the child
		// while (cmd->next->pipfd2[READ_FD] != -1 && cmd->next->pipfd2[WRITE_FD] != -1)
	}
}

void	close_the_shit(t_cmd *cmd)
{
	if (cmd->resetfd[IN] != -1 && dup2(cmd->resetfd[IN], STDIN_FILENO) == -1)
		put_error("Failed to reset STDIN");
	if (cmd->resetfd[OUT] != -1 && dup2(cmd->resetfd[OUT], STDOUT_FILENO) == -1)
		put_error("Failed to reset STDIN");
	cmd->resetfd[IN] = -1;
	cmd->resetfd[OUT] = -1;
}

void	dup_redir(t_cmd *cmd)
{
	if (cmd->pipfd[IN] != -1)
	{
		cmd->resetfd[IN] = dup(STDIN);
		dprintf(2, "Dup2 FD in : %d\n", cmd->pipfd[IN]);
		if (cmd->pipfd[IN] != -1 &&
				dup2(cmd->pipfd[IN], STDIN_FILENO) == -1)
			put_error("Failed to dup STDIN");
		if (cmd->pipfd[IN] != -1)
			close(cmd->pipfd[IN]);
	}
	if (cmd->pipfd[OUT] != -1)
	{
		cmd->resetfd[OUT] = dup(STDOUT);
		dprintf(2, "Dup2 FD out : %d\n", cmd->pipfd[OUT]);
		if (cmd->pipfd[OUT] != -1 &&
					dup2(cmd->pipfd[OUT], STDOUT_FILENO) == -1)
			put_error("Failed to dup STDOUT");
		if (cmd->pipfd[OUT] != -1)
			close(cmd->pipfd[OUT]);
	}
}

void	cmd_dispatch(t_cmd *cmd, t_var **env, char **envp, t_pid *pid)
{

	if (cmd->pipfd[IN] != -1 || cmd->pipfd[OUT] != -1)
		dup_redir(cmd);
	if (cmd->builtin)
	{
		// is there a '|', if there is FORK if not, dup2 all the according
		// fds. If there is a '|', fork and then run.
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
		if (cmd->pipfd[IN] != -1 || cmd->pipfd[OUT] != -1)
			close_the_shit(cmd);
	}
	else
		ft_exec(cmd, *env, envp, pid);
	if (cmd->pipfd[IN] != -1 || cmd->pipfd[OUT] != -1)
		close_the_shit(cmd);
}
